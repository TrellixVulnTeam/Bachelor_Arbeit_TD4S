//
// Created by 01100 on 15/08/2020.
//

#define DEBUG_NN 0

#ifndef VTR_NEURAL_NETWORK_H
#define VTR_NEURAL_NETWORK_H

#include <cstdlib>

#include <cstdio>
#include <iostream>
#include <string>

#include "tensorflow/c/c_api.h"

//TODO remove unused imports

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
#include "../util/histogram.h" // specified import more precisely because of header file with same name in tensorflow package
#include "place_util.h"
#include "place_delay_model.h"

#define CNN_INPUT_GRID_SIZE 64
#define LSTM_ENTRY_POINT "serving_default_lstm_2_input"
#define CNN_ENTRY_POINT "serving_default_conv2d_2_input"


class TfModelInterface {
public:

    /// TODO
    void init(const char *saved_model_dir, const char *nn_input_entry_point);

    /// destructor freeing explicitly allocated memory
    ~TfModelInterface();

    /// Predicts the wiring cost of the current placement of the passed net, or returns -1 to fall back to HPWL
    /// \param net_id the net to compute the cost of
    /// \param bbptr the bounding box of this net
    /// \return if terminal count <= 3: -1; else: the predicted wiring cost if prediction succeeded, -1 else
    float predict_wiring_cost(ClusterNetId net_id, t_bb* bbptr);

#if DEBUG_NN
    /// debug method to test NN integration. generates a minimal sample of already mapped coordinates and directly
    /// calls encode_and_predict(...)
    /// \return a positive value if prediction succeeded
    virtual float debug() = 0;
#endif

protected:

    /// performs NN inference of a readily encoded sample
    /// \param InputValues the encoded sample
    /// \return the predicted cost value, which might need post-processing
    float predict(TF_Tensor **InputValues);

    /// maps terminal coordinates of the given net onto appropriate input format for NN and then calls encode_and_predict(...) to get
    /// the predicted wiring cost of the net
    /// \param net_id the net to compute the cost of
    /// \param bbptr the bounding box of this net
    /// \param number_of_terminals the total number of terminals in this net
    /// \param cluster_ctx VPR internal data structure holding the temporary placement
    /// \return the post-processed cost of the current placement of the passed net
    virtual float preprocess_and_predict(ClusterNetId net_id, t_bb* bbptr, unsigned long number_of_terminals,
            const ClusteringContext& cluster_ctx) = 0;

    /// encodes the mapped terminal coordinates as tensorflow input and calls predict(...) to get the raw predicted cost
    /// \param mapped_input terminal coordinates of a net mapped onto appropriate input format for NN
    /// \param terminal_count the total number of terminals in that net
    /// \return the predicted cost value, which might need post-processing
    virtual float encode_and_predict(void* mapped_input, unsigned long  terminal_count) = 0;

    /// number of input samples per prediction
    int NumInputs;
    /// reusable tensor for the NN to temporarily store its input in
    TF_Tensor **InputValues;

private:

    /// tensorflow session object representing a loadad NN
    TF_Session *Session;
    /// number of output samples per prediction
    int NumOutputs;
    /// malloced space for holding NN Output
    TF_Output *Output;
    /// malloced space for holding NN Input
    TF_Output *Input;
    /// tensorflow object representing some internal status, required for creating a session
    TF_Status *Status;
    /// tensorflow object representing the computation graph of the NN
    TF_Graph *Graph;
    /// tensorflow object representing options for initializing the session
    TF_SessionOptions *SessionOpts;
    /// reusable tensor for the NN to temporarily store the result in
    TF_Tensor **OutputValues;

};

class LSTM: public TfModelInterface {
public:
    LSTM();
#if DEBUG_NN
    float debug() override;
#endif
protected:
    float preprocess_and_predict(ClusterNetId net_id, t_bb* bbptr, unsigned long number_of_terminals,
                                 const ClusteringContext& cluster_ctx) override;
    float encode_and_predict(void* mapped_input, unsigned long  terminal_count) override;
};

class CNN: public TfModelInterface {
public:
    CNN();
#if DEBUG_NN
    float debug() override;
#endif
protected:
    float preprocess_and_predict(ClusterNetId net_id, t_bb* bbptr, unsigned long number_of_terminals,
                                 const ClusteringContext& cluster_ctx) override;
    float encode_and_predict(void* mapped_input, unsigned long  terminal_count) override;
};


#endif //VTR_NEURAL_NETWORK_H
