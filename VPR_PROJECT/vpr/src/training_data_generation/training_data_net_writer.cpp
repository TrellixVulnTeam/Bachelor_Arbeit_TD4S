using namespace std;

#include "training_data_net_writer.h"



static unordered_map<ClusterNetId, uint16_t> net_update_counter;

static string current_design_base_path;

static void init_net_printing_structures() {

	cout << "please specify training data output base path (ending with '/').";
	cin.ignore();
	getline(cin, current_design_base_path);

	std::stringstream ss;
	ss << current_design_base_path << "test.txt";

	ofstream test_file(ss.str(), ios::out | ios::trunc);
	while (!test_file.is_open()) {
		cout << "specified invalid path, please try again.";
		cin.ignore();
		getline(cin, current_design_base_path);
		test_file.open(ss.str(), ios::out | ios::trunc);
	}
	test_file.close();

	net_update_counter = {};

	auto& cluster_ctx = g_vpr_ctx.clustering();

	for (auto net_id : cluster_ctx.clb_nlist.nets()) { /* for each net ... */
		net_update_counter.insert(pair<ClusterNetId, uint16_t>(net_id, 0));
	}
}

/*
generates training data and saves it
*/
static void generate_training_data(ClusterNetId net_id, t_bb* bbptr, float cost) {

	print_current_net_placement(net_id, bbptr, cost);

}

class Compare
{
public:
	bool operator() (const routing_block_struct a, const routing_block_struct b)
	{
		return a.cost > b.cost;
	}
};

static uint16_t compute_min_wiring_cost(ClusterNetId net_id, const t_bb* bbptr) {
	const uint16_t x_size = bbptr->xmax - bbptr->xmin;
	const uint16_t y_size = bbptr->ymax - bbptr->ymin;
	routing_block_struct** routing_grid = (routing_block_struct**) malloc(x_size * y_size * sizeof(routing_block_struct));//new routing_block_struct[x_size][y_size];

	for (int i = 0; i < x_size; i++) {
		for (int j = 0; j < y_size; j++) {
			routing_grid[i][j].is_sink = false;
			routing_grid[i][j].is_sink = false;
			routing_grid[i][j].x = i;
			routing_grid[i][j].y = j;
			routing_grid[i][j].cost = ((uint16_t) 0x0000);
		}
	}

	uint16_t total_cost;

	std::priority_queue<routing_block_struct, vector<routing_block_struct>, Compare> queue;
	std::list<routing_block_struct> reached_sinks;

	auto& cluster_ctx = g_vpr_ctx.clustering();
	auto& place_ctx = g_vpr_ctx.placement();
	ClusterBlockId bnum;
	int pnum;

	uint16_t sinks_left = 0;
	for (auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
		sinks_left++;
		bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
		pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
		routing_grid[place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum] - bbptr->xmin][place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum] - bbptr->ymin].is_sink = true;
	}

	//start with source
	bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
	pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);
	routing_block_struct active = routing_grid[place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum] - bbptr->xmin][place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum] - bbptr->ymin];
	//uint16_t active_x = place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum] - bbptr->xmin;
	//uint16_t active_y = place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum] - bbptr->ymin;
	routing_grid[active.x][active.y].cost = 0;
	routing_grid[active.x][active.y].in_queue = true; //source never in queue, but always in_queue==true

	routing_block_struct source = active;

	if (source.x > 0) {
		routing_grid[source.x - 1][source.y].cost = 1;
		routing_grid[source.x - 1][source.y].direction = 2;
		queue.push(routing_grid[source.x - 1][source.y]);
	}
	if (source.y > 0) {
		routing_grid[source.x][source.y - 1].cost = 1;
		routing_grid[source.x][source.y - 1].direction = 1;
		queue.push(routing_grid[source.x][source.y - 1]);
	}
	if (source.x < x_size - 1) {
		routing_grid[source.x + 1][source.y].cost = 1;
		routing_grid[source.x + 1][source.y].direction = 0;
		queue.push(routing_grid[source.x + 1][source.y]);
	}
	if (source.y < y_size - 1) {
		routing_grid[source.x][source.y + 1].cost = 1;
		routing_grid[source.x][source.y + 1].direction = 3;
		queue.push(routing_grid[source.x][source.y + 1]);
	}

	//route all sinks
	while (sinks_left > 0) {

		//get starting point from already routed
		active = queue.top();
		queue.pop();
		active.in_queue = false;
		while (!active.is_sink || active.cost == 0) {
			if (active.x > 0) {
				routing_grid[active.x - 1][active.y].cost = 1;
				routing_grid[active.x - 1][active.y].direction = 2;
				queue.push(routing_grid[active.x - 1][active.y]);
			}
			if (active.y > 0) {
				routing_grid[active.x][active.y - 1].cost = 1;
				routing_grid[active.x][active.y - 1].direction = 1;
				queue.push(routing_grid[active.x][active.y - 1]);
			}
			if (active.x < x_size - 1) {
				routing_grid[active.x + 1][active.y].cost = 1;
				routing_grid[active.x + 1][active.y].direction = 0;
				queue.push(routing_grid[active.x + 1][active.y]);
			}
			if (active.y < y_size - 1) {
				routing_grid[active.x][active.y + 1].cost = 1;
				routing_grid[active.x][active.y + 1].direction = 3;
				queue.push(routing_grid[active.x][active.y + 1]);
			}
			active = queue.top();
			queue.pop();
			active.in_queue = false;
		}
		//sink reached
		reached_sinks.push_front(active);
		sinks_left--;
		total_cost += active.cost;

		//clear queue
		while (!queue.empty()) {
			active = queue.top();
			queue.pop();
			active.in_queue = false;
		}

		//add already routed connections with cost of 0
		for (routing_block_struct sink : reached_sinks) {
			active = sink;
			while (!active.in_queue) {
				active.cost = 0;
				active.in_queue = true;
				queue.push(active);
				switch (active.direction) {
				case 0:
					active = routing_grid[active.x - 1][active.y];
					break;
				case 1:
					active = routing_grid[active.x][active.y + 1];
					break;
				case 2:
					active = routing_grid[active.x + 1][active.y];
					break;
				case 3:
					active = routing_grid[active.x][active.y - 1];
					break;
				default:
					break;
				}
			}
		}

		//add segements around source (source is not added anymore), but only if not already added
		if (source.x > 0) {
			if (!routing_grid[source.x - 1][source.y].in_queue) {
				routing_grid[source.x - 1][source.y].in_queue = true;
				queue.push(routing_grid[source.x - 1][source.y]);
			}
		}
		if (source.y > 0) {
			if (!routing_grid[source.x][source.y - 1].in_queue) {
				routing_grid[source.x][source.y - 1].in_queue = true;
				queue.push(routing_grid[source.x][source.y - 1]);
			}
		}
		if (source.x < x_size - 1) {
			if (!routing_grid[source.x + 1][source.y].in_queue) {
				routing_grid[source.x + 1][source.y].in_queue = true;
				queue.push(routing_grid[source.x + 1][source.y]);
			}
		}
		if (source.y < y_size - 1) {
			if (!routing_grid[source.x][source.y + 1].in_queue) {
				routing_grid[source.x][source.y + 1].in_queue = true;
				queue.push(routing_grid[source.x][source.y + 1]);
			}
		}

		//active path added with cost of 0; segments around source not on path added with cost 1
	}

	//finished, total_cost holds the exact routing cost, actual routing is irrelevant, so no need to output it...
	free(routing_grid);
	return total_cost;
}

/*
outputs the current placement of the net to a new file
*/
static void print_current_net_placement(ClusterNetId net_id, t_bb* bbptr, float cost) {

	uint16_t number_of_updates = net_update_counter.find(net_id)->second;
	net_update_counter.insert(pair<ClusterNetId, uint16_t>(net_id, number_of_updates + 1)); //TODO check

	auto& cluster_ctx = g_vpr_ctx.clustering();
	auto& place_ctx = g_vpr_ctx.placement();

	ClusterBlockId bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
	int pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);

	std::stringstream ss;
	ss << current_design_base_path << size_t(net_id) << "/" << number_of_updates << ".txt";

	ofstream current_net_placement_file(ss.str(), ios::out | ios::trunc);
	if (current_net_placement_file.is_open())
	{
		current_net_placement_file << "% pin coordinates in x;y pairs, first source, then all sinks, finally HPWL cost (added later)\n";
		current_net_placement_file << "% net id: ";
		current_net_placement_file << size_t(net_id);
		current_net_placement_file << "\n";

		current_net_placement_file << "%source:\n";
		current_net_placement_file << place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
		current_net_placement_file << ";";
		current_net_placement_file << place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
		current_net_placement_file << "% block num: ";
		current_net_placement_file << size_t(bnum);
		current_net_placement_file << ", pin num: ";
		current_net_placement_file << pnum;
		current_net_placement_file << "\n";

		current_net_placement_file << "%sinks:\n";

		int i = 0;
		for (auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
			i++;
			bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
			pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
			current_net_placement_file << place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
			current_net_placement_file << ";";
			current_net_placement_file << place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
			current_net_placement_file << "% block num: ";
			current_net_placement_file << size_t(bnum);
			current_net_placement_file << ", pin num: ";
			current_net_placement_file << pnum;
			current_net_placement_file << "\n";
		}

		current_net_placement_file << "% pure HPWL (half bounding box perimeter) from VPR:\n";
		current_net_placement_file << (bbptr->xmax - bbptr->xmin + 1) + (bbptr->ymax - bbptr->ymin + 1);
		current_net_placement_file << "\n";
		current_net_placement_file << "% wiring cost (corrected HPWL) from VPR:\n";
		current_net_placement_file << cost;
		current_net_placement_file << "\n";
		current_net_placement_file << "% pseudo exact wiring cost (min path through grid):\n";
		current_net_placement_file << compute_min_wiring_cost(net_id, bbptr);
		current_net_placement_file << "\n";

		current_net_placement_file.close();
	}
	else cout << "Unable to open file";
}