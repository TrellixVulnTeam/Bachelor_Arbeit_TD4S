using namespace std;

//TODO remove unnecessary imports

#include "vtr_assert.h"
#include "vtr_log.h"
#include "vtr_util.h"
#include "vtr_random.h"

#include "vpr_types.h"
#include "vpr_error.h"
#include "vpr_utils.h"

#include "globals.h"
#include "place.h"
#include "read_place.h"
#include "draw.h"
#include "place_and_route.h"
#include "net_delay.h"
#include "timing_place_lookup.h"
#include "timing_place.h"
#include "read_xml_arch_file.h"
#include "echo_files.h"
#include "vpr_utils.h"
#include "place_macro.h"
#include "histogram.h"
#include "place_util.h"
#include "place_delay_model.h"

static void save_current_net_placement(ClusterNetId net_id, const ClusteringContext &cluster_ctx) {

}