#ifndef VPR_PLACE_H
#define VPR_PLACE_H

/*
 * compile-time switch to choose the mode of operation:
 * 0: is legacy = unchanged code
 * 1: is training data generation: logging of all tested net placements with wiring cost into text file
 * 2: is unused
 * 3: is ml_integration LSTM = wiring cost estimation via LSTM NN, includes features of reference
 * 4: is ml_integration CNN = wiring cost estimation via CNN NN, includes features of reference
 */
#define MODE 3
/// enables debugging of NN integration and training data generation
#define DEBUG_NN_INTEGRATION 0

#include "vpr_types.h"
void try_place(t_placer_opts placer_opts,
		t_annealing_sched annealing_sched,
        t_router_opts router_opts,
        const t_analysis_opts& analysis_opts,
		t_chan_width_dist chan_width_dist, 
		t_det_routing_arch *det_routing_arch, std::vector<t_segment_inf>& segment_inf,
        t_direct_inf *directs, int num_directs);

#endif
