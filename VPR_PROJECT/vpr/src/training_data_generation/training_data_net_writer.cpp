using namespace std;

#include "training_data_net_writer.h"



struct routing_block_struct {
    bool is_sink, in_queue;
    uint16_t x, y, cost;
    uint8_t direction; //from: 0 left, 1 above, 2 right, 3 below
};


string current_design_base_path;

static void print_current_net_placement(ClusterNetId net_id, t_bb* bbptr, float cost);

//static uint16_t compute_min_wiring_cost(ClusterNetId net_id, t_bb* bbptr);

void init_net_printing_structures() {

	cout << "please specify training data output path (ending with '.txt').\n";
	cin.ignore();
	getline(cin, current_design_base_path);

	std::stringstream ss;
	ss << "/" << current_design_base_path << "test.txt";

	ofstream test_file(ss.str(), ios::out | ios::trunc);
	while (!test_file.is_open()) {
		cout << "specified invalid path: '" << ss.str() << "', please try again.\n";
		cin.ignore();
		getline(cin, current_design_base_path);
		test_file.open(ss.str(), ios::out | ios::trunc);
	}
	test_file.close();

}

/*
generates training data and saves it
*/
void generate_training_data(ClusterNetId net_id, t_bb* bbptr, float cost) {

    //ignore nets where all sinks have been moved to the location of the source (due to moving perimeter blocks inside for BB computation)
    if(bbptr->xmax - bbptr->xmin != 0 || bbptr->ymax - bbptr->ymin != 0) {
        print_current_net_placement(net_id, bbptr, cost);
    }

}

class Compare
{
public:
	bool operator() (const routing_block_struct* a, const routing_block_struct* b)
	{
		return a->cost > b->cost;
	}
};

static uint16_t compute_min_wiring_cost(ClusterNetId net_id, const t_bb* bbptr) {

    //cout << "started finding shortest route\n";

	const uint16_t x_size = (bbptr->xmax - bbptr->xmin) + 1;
	const uint16_t y_size = (bbptr->ymax - bbptr->ymin) + 1;
	//cout << "grid size: " << x_size << ";" << y_size << "\n";
	//routing_block_struct** routing_grid = (routing_block_struct**) malloc(x_size * y_size * sizeof(routing_block_struct));//new routing_block_struct[x_size][y_size];
    //cout << "grid matrix malloced, size: " << x_size * y_size << "\n";
    routing_block_struct routing_grid[x_size][y_size][1];
    for (int i = 0; i < x_size; i++) {
        //cout <<"flag 0\n";
		for (int j = 0; j < y_size; j++) {
		    //cout << "accessing element: " << i << "," << j << "\n";
		    //cout << routing_grid[i][j]->cost;
			routing_grid[i][j]->is_sink = false;
			//cout <<"flag 1\n";
			routing_grid[i][j]->in_queue = false;
			routing_grid[i][j]->x = i;
			routing_grid[i][j]->y = j;
			routing_grid[i][j]->cost = ((uint16_t) 0xFFFF);
            //cout <<"flag 2\n";
		}
	}

	//cout << "initialized routing grid\n";

	uint16_t total_cost= 0;

	std::priority_queue<routing_block_struct*, vector<routing_block_struct*>, Compare> queue;
	std::list<routing_block_struct*> reached_sinks;

	//cout << "created priority queue and reached sinks list\n";

	auto& cluster_ctx = g_vpr_ctx.clustering();
	auto& place_ctx = g_vpr_ctx.placement();
    auto& device_ctx = g_vpr_ctx.device();
    auto& grid = device_ctx.grid;
	ClusterBlockId bnum;
	int pnum;

	//cout << "retrieved vpr structures\n";

	uint16_t sinks_left = 0;
	for (auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
	    //cout << "handling one sink\n";
		sinks_left++;
		bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
		pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
        int x = place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
        int y = place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
        x = max(min<int>(x, grid.width() - 2), 1); //-2 for no perim channels
        y = max(min<int>(y, grid.height() - 2), 1); //-2 for no perim channels
		//cout << "accessing grid matrix, indices are: " << x - bbptr->xmin << ", " << y - bbptr->ymin << "; grid size is: " << x_size << ";" << y_size << "\n";

		if(routing_grid[x - bbptr->xmin][y - bbptr->ymin]->is_sink == true){
		    //cout << "two sinks at same location: " << x - bbptr->xmin << "," << y - bbptr->ymin << "\n";
            sinks_left--;
		}
		else {
            routing_grid[x - bbptr->xmin][y - bbptr->ymin]->is_sink = true;
        }
	}

	//cout << "sinks counted and linked to matrix\n";

	//start with source
	bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
	pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);
	int x = place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
    int y = place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
    x = max(min<int>(x, grid.width() - 2), 1); //-2 for no perim channels
    y = max(min<int>(y, grid.height() - 2), 1); //-2 for no perim channels
    //cout << "source at: " << x - bbptr->xmin << "," << y - bbptr->ymin << "\n";

    if(routing_grid[x - bbptr->xmin][y - bbptr->ymin]->is_sink == true){ //source is already a sink
        //cout << "source at same location as a sink: " << x - bbptr->xmin << "," << y - bbptr->ymin << "\n";
        sinks_left--;
    }

    routing_block_struct* active = routing_grid[x - bbptr->xmin][y - bbptr->ymin];
	//uint16_t active_x = place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum] - bbptr->xmin;
	//uint16_t active_y = place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum] - bbptr->ymin;
	routing_grid[active->x][active->y]->cost = 0;
	routing_grid[active->x][active->y]->in_queue = true; //source never in queue, but always in_queue==true
    //cout << routing_grid[active->x][active->y]->in_queue << "\n";
    //cout << "source at: " << active->x << "," << active->y << "\n";
    //cout << active->in_queue << "\n";
	//cout << routing_grid[active->x][active->y]->in_queue << "\n";

	routing_block_struct* source = active;

	//cout << "source visited\n";

	if (source->x > 0) {
		routing_grid[source->x - 1][source->y]->cost = 1;
		routing_grid[source->x - 1][source->y]->direction = 2;
		queue.push(routing_grid[source->x - 1][source->y]);
	}
	if (source->y > 0) {
		routing_grid[source->x][source->y - 1]->cost = 1;
		routing_grid[source->x][source->y - 1]->direction = 1;
		queue.push(routing_grid[source->x][source->y - 1]);
	}
	if (source->x < x_size - 1) {
		routing_grid[source->x + 1][source->y]->cost = 1;
		routing_grid[source->x + 1][source->y]->direction = 0;
		queue.push(routing_grid[source->x + 1][source->y]);
	}
	if (source->y < y_size - 1) {
		routing_grid[source->x][source->y + 1]->cost = 1;
		routing_grid[source->x][source->y + 1]->direction = 3;
		queue.push(routing_grid[source->x][source->y + 1]);
	}

	//cout << "neighbours of source handled\n";

	//route all sinks
	while (sinks_left > 0) {

	    //cout << "routing to one sink, sinks left: " << sinks_left << "\n";

		//get starting point from already routed
		active = queue.top();
		queue.pop();
		active->in_queue = false;
        //cout << "accessing position: " << active->x << "," << active->y << "\n";
		while (!active->is_sink) {
//		    //cout << "accessing position: " << active->x << "," << active->y << "\n";
			if (active->x > 0) {
			    if(routing_grid[active->x - 1][active->y]->cost > active->cost + 1) {
                    routing_grid[active->x - 1][active->y]->cost = active->cost + 1;
                    routing_grid[active->x - 1][active->y]->direction = 2;
                    queue.push(routing_grid[active->x - 1][active->y]);
                }
			}
			if (active->y > 0) {
                if(routing_grid[active->x][active->y - 1]->cost > active->cost + 1) {
                    routing_grid[active->x][active->y - 1]->cost = active->cost + 1;
                    routing_grid[active->x][active->y - 1]->direction = 1;
                    queue.push(routing_grid[active->x][active->y - 1]);
                }
			}
			if (active->x < x_size - 1) {
                if(routing_grid[active->x + 1][active->y]->cost > active->cost + 1) {
                    routing_grid[active->x + 1][active->y]->cost = active->cost + 1;
                    routing_grid[active->x + 1][active->y]->direction = 0;
                    queue.push(routing_grid[active->x + 1][active->y]);
                }
			}
			if (active->y < y_size - 1) {
                if(routing_grid[active->x][active->y + 1]->cost > active->cost + 1) {
                    routing_grid[active->x][active->y + 1]->cost = active->cost + 1;
                    routing_grid[active->x][active->y + 1]->direction = 3;
                    queue.push(routing_grid[active->x][active->y + 1]);
                }
			}
			active = queue.top();
			queue.pop();
			active->in_queue = false;
		}
		//sink reached
		reached_sinks.push_front(active);
		active->is_sink= false;
		sinks_left--;
		total_cost += active->cost;

		//cout << "sink reached\n";

		//clear queue
		while (!queue.empty()) {
			active = queue.top();
			queue.pop();
			active->in_queue = false;
		}

		//cout << "queue cleared\n";

		//reset costs for next iteration
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < y_size; j++) {
                routing_grid[i][j]->cost = ((uint16_t) 0xFFFF);
            }
        }

		//add already routed connections with cost of 0
		for (routing_block_struct* sink : reached_sinks) {
			active = sink;
			while (!active->in_queue) {
				active->cost = 0;
				active->in_queue = true;
				queue.push(active);
				switch (active->direction) {
				case 0:
					active = routing_grid[active->x - 1][active->y];
					break;
				case 1:
					active = routing_grid[active->x][active->y + 1];
					break;
				case 2:
					active = routing_grid[active->x + 1][active->y];
					break;
				case 3:
					active = routing_grid[active->x][active->y - 1];
					break;
				default:
					break;
				}
			}
		}

		//cout << "already routed path added to queue\n";

		//add segements around source (source is not added anymore), but only if not already added
		if (source->x > 0) {
		    //cout << "adding left neighbour\n";
			if (!routing_grid[source->x - 1][source->y]->in_queue) {
				routing_grid[source->x - 1][source->y]->in_queue = true;
				queue.push(routing_grid[source->x - 1][source->y]);
			}
		}
		if (source->y > 0) {
            //cout << "adding bottom neighbour\n";
			if (!routing_grid[source->x][source->y - 1]->in_queue) {
				routing_grid[source->x][source->y - 1]->in_queue = true;
				queue.push(routing_grid[source->x][source->y - 1]);
			}
		}
		if (source->x < x_size - 1) {
            //cout << "adding right neighbour\n";
			if (!routing_grid[source->x + 1][source->y]->in_queue) {
				routing_grid[source->x + 1][source->y]->in_queue = true;
				queue.push(routing_grid[source->x + 1][source->y]);
			}
		}
		if (source->y < y_size - 1) {
            //cout << "adding top neighbour\n";
			if (!routing_grid[source->x][source->y + 1]->in_queue) {
				routing_grid[source->x][source->y + 1]->in_queue = true;
				queue.push(routing_grid[source->x][source->y + 1]);
			}
		}

		//cout << "blocks adjacent to source added to queue\n";
		//active path added with cost of 0; segments around source not on path added with cost 1
	}

	//cout << "finished routing\n";
	//finished, total_cost holds the exact routing cost, actual routing is irrelevant, so no need to output it...
	//free(routing_grid);
	return total_cost;
}

/*
outputs the current placement of the net to a new file
*/
static void print_current_net_placement(ClusterNetId net_id, t_bb* bbptr, float cost) {

    auto& device_ctx = g_vpr_ctx.device();
    auto& grid = device_ctx.grid;

	auto& cluster_ctx = g_vpr_ctx.clustering();
	auto& place_ctx = g_vpr_ctx.placement();

	ClusterBlockId bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
	int pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);

	std::stringstream ss;
	ss << "/" << current_design_base_path;

	ofstream current_net_placement_file(ss.str(), ios::out | ios::app);
	if (current_net_placement_file.is_open())
	{
//		current_net_placement_file << "% pin coordinates in x;y pairs, first source, then all sinks\n";
//		current_net_placement_file << "% net id: ";
//		current_net_placement_file << size_t(net_id);
//		current_net_placement_file << "\n";

//        current_net_placement_file << "%BB size: \n";
        current_net_placement_file << bbptr->xmax - bbptr->xmin;
        current_net_placement_file << ",";
        current_net_placement_file << bbptr->ymax - bbptr->ymin;
        current_net_placement_file << "\n";

//		current_net_placement_file << "%source, then sinks, relative coords in BB: \n";
		int x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
		current_net_placement_file << max(min<int>(x, grid.width() - 2), 1) - bbptr->xmin;
		current_net_placement_file << ",";
		int y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
		current_net_placement_file << max(min<int>(y, grid.height() - 2), 1) - bbptr->ymin;

		int i = 0;
		for (auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
            current_net_placement_file << ";";
			i++;
			bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
			pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
            x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
            current_net_placement_file << max(min<int>(x, grid.width() - 2), 1) - bbptr->xmin;
			current_net_placement_file << ",";
            y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];
            current_net_placement_file << max(min<int>(y, grid.height() - 2), 1) - bbptr->ymin;
		}

        current_net_placement_file << "\n";

//		current_net_placement_file << "% pure HPWL (half bounding box perimeter) from VPR:\n";
//		current_net_placement_file << (bbptr->xmax - bbptr->xmin + 1) + (bbptr->ymax - bbptr->ymin + 1);
//		current_net_placement_file << "\n";
//		current_net_placement_file << "% wiring cost (corrected HPWL) from VPR:\n";
//		current_net_placement_file << cost;
//		current_net_placement_file << "\n";
//		current_net_placement_file << "% pseudo exact wiring cost (min path through grid):\n";
		current_net_placement_file << compute_min_wiring_cost(net_id, bbptr);
		current_net_placement_file << "\n";

		current_net_placement_file.close();
	}
	else cout << "Unable to open file\n";
}