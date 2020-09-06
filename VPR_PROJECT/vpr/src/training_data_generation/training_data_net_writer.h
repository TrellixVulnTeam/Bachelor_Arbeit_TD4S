#pragma once


#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vpr_types.h"

#include "globals.h"
#include "place.h"

/// initializes the structures necessary to log net placements and to compute their "true cost" using the maze algorithm
void init_net_printing_structures();

/// logs the current placement, corrected HPWL cost and "true cost" of the given net
/// \param net_id the net to log the placement of
/// \param bbptr the bounding box of the given net
/// \param cost the corrected HPWL cost of its current placement
void generate_training_data(ClusterNetId net_id, t_bb* bbptr, float cost);
