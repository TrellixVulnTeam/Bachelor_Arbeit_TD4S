#pragma once


#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//#include "vtr_assert.h"
//#include "vtr_log.h"
//#include "vtr_util.h"
//#include "vtr_random.h"

#include "vpr_types.h"
//#include "vpr_error.h"
//#include "vpr_utils.h"

#include "globals.h"
#include "place.h"
//#include "read_place.h"
//#include "draw.h"
//#include "place_and_route.h"
//#include "net_delay.h"
//#include "timing_place_lookup.h"
//#include "timing_place.h"
//#include "read_xml_arch_file.h"
//#include "echo_files.h"
//#include "vpr_utils.h"
//#include "place_macro.h"
//#include "../util/histogram.h" // specified import more precisely because of header file with same name in tensorflow package
//#include "place_util.h"
//#include "place_delay_model.h"

/// initializes the structures necessary to log net placements and to compute their "true cost" using the maze algorithm
void init_net_printing_structures();

/// logs the current placement, corrected HPWL cost and "true cost" of the given net
/// \param net_id the net to log the placement of
/// \param bbptr the bounding box of the given net
/// \param cost the corrected HPWL cost of its current placement
void generate_training_data(ClusterNetId net_id, t_bb* bbptr, float cost);
