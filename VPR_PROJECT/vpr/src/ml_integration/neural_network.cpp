//
// Created by 01100 on 15/08/2020.
//

#include "neural_network.h"

void NoOpDeallocator(void* data, size_t a, void* b) {}

void TfModelInterface::init(const char *saved_model_dir, const char *nn_input_entry_point) {
    //********* Read model
#if DEBUG_NN
    printf("hello world.\n");
#endif

    Graph = TF_NewGraph();
    Status = TF_NewStatus();
    SessionOpts = TF_NewSessionOptions();
    TF_Buffer *RunOpts = nullptr;

    const char *tags = "serve";
    int ntags = 1;

#if DEBUG_NN
    printf("trying to load model.\n");
#endif
    Session = TF_LoadSessionFromSavedModel(SessionOpts, RunOpts, saved_model_dir, &tags, ntags,
                                           Graph, nullptr, Status);

#if DEBUG_NN
    if (TF_GetCode(Status) == TF_OK) {
        printf("TF_LoadSessionFromSavedModel OK\n");
    } else {
        printf("%s", TF_Message(Status));
    }
#endif


    //****** Get input tensor
    NumInputs = 1;
    Input = static_cast<TF_Output *>(malloc(sizeof(TF_Output) * NumInputs));
    TF_Output t0 = {TF_GraphOperationByName(Graph, nn_input_entry_point), 0};

#if DEBUG_NN
    if (t0.oper == nullptr) {
        printf("ERROR: Failed TF_GraphOperationByName ");
        printf("%s", nn_input_entry_point);
        printf("\n");
    }
    else {
        printf("TF_GraphOperationByName ");
        printf("%s", nn_input_entry_point);
        printf(" is OK\n");
    }
#endif

    Input[0] = t0;


    //********* Get Output tensor
    NumOutputs = 1;
    Output = static_cast<TF_Output *>(malloc(sizeof(TF_Output) * NumOutputs));
    TF_Output t2 = {TF_GraphOperationByName(Graph, "StatefulPartitionedCall"), 0};

#if DEBUG_NN
    if (t2.oper == nullptr)
        printf("ERROR: Failed TF_GraphOperationByName StatefulPartitionedCall\n");
    else
        printf("TF_GraphOperationByName StatefulPartitionedCall is OK\n");
#endif

    Output[0] = t2;

    InputValues = (TF_Tensor **) malloc(sizeof(TF_Tensor *) * NumInputs);
    // allocate actual output tensor
    OutputValues = (TF_Tensor **) malloc(sizeof(TF_Tensor *) * NumOutputs);

#if DEBUG_NN
    debug();
#endif

    counter = 0; // TODO

}

TfModelInterface::~TfModelInterface() {
    // Free memory
    TF_DeleteGraph(Graph);
    TF_DeleteSession(Session, Status);
    TF_DeleteSessionOptions(SessionOpts);
    TF_DeleteStatus(Status);
    free(InputValues);
    free(OutputValues);
}

float TfModelInterface::predict_wiring_cost(ClusterNetId net_id, t_bb* bbptr) {

    auto& cluster_ctx = g_vpr_ctx.clustering();

    unsigned long number_of_terminals = cluster_ctx.clb_nlist.net_sinks(net_id).size() + 1;

    if(number_of_terminals <= 3)
        return -1;

    return preprocess_and_predict(net_id, bbptr, number_of_terminals, cluster_ctx);

}

float TfModelInterface::predict() {

    counter++;

//    if(counter > 186410)
//        printf("counter: %d\n", counter); // TODO

    // Run the Session
    TF_SessionRun(Session, nullptr, Input, InputValues, NumInputs, Output,
            OutputValues, NumOutputs, nullptr, 0, nullptr, Status);

#if DEBUG_NN
    if (TF_GetCode(Status) == TF_OK){
        printf("Session is OK\n");
    }
    else{
        printf("%s", TF_Message(Status));
        printf("\n");
    }
#endif

    void* buff = TF_TensorData(OutputValues[0]);
    auto* prediction = static_cast<float *>(buff);
#if DEBUG_NN
    printf("Result Tensor :\n");
    printf("%f\n",prediction[0]);

    #if DEBUG_NN_INTERACTIVE
        std::cin.ignore();
        std::string tmp;
        getline(std::cin, tmp);
    #endif
#endif

    TF_DeleteTensor(OutputValues[0]); // TODO

    return prediction[0];
}

/*
 * LSTM
 */

LSTM::LSTM() {
    // set model dir
    const char *saved_model_dir = "src/ml_integration/model_lstm/model/";
    // init the NN with correct input entry point
    init(saved_model_dir, LSTM_ENTRY_POINT);
}

#if DEBUG_NN
float LSTM::debug() {
    float tmp[1][3][2] = {{
                                  {0.0,1.0},
                                  {1.0,0.5},
                                  {0.3,0.3},
                          },};
    return encode_and_predict(((void*) tmp), 3);
}
#endif

float LSTM::preprocess_and_predict(ClusterNetId net_id, t_bb* bbptr, unsigned long number_of_terminals,
                                   const ClusteringContext& cluster_ctx) {
    //convert net to list of terminal coords (array)
    // auto& device_ctx = g_vpr_ctx.device();
    // auto& grid = device_ctx.grid;
    auto& place_ctx = g_vpr_ctx.placement();

    ClusterBlockId bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
    int pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);

    int x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
    int y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];

    float terminal_coords[1][number_of_terminals][2];

    float bb_size = std::max(bbptr->xmax - bbptr->xmin, bbptr->ymax - bbptr->ymin);

    terminal_coords[0][0][0] = ((float) x - bbptr->xmin) / bb_size;
    terminal_coords[0][0][1] = ((float) y - bbptr->ymin) / bb_size;

    int i = 1;
    for(auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
        bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
        pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
        x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
        y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];

        terminal_coords[0][i][0] = ((float) x - bbptr->xmin) / bb_size;
        terminal_coords[0][i][1] = ((float) y - bbptr->ymin) / bb_size;
        i++;
    }

    //call predict method
    return encode_and_predict(((void*) terminal_coords), number_of_terminals) * bb_size;
}

float LSTM::encode_and_predict(void* mapped_input, unsigned long terminal_count) {

    int ndims = 3;
    int64_t dims[] = {1, static_cast<int64_t>(terminal_count), 2};
    // ((float (*)[terminal_count][2]) terminal_coords)
    // float data[1][terminal_count][2];
#if DEBUG_NN
    for(unsigned long i = 0; i < terminal_count; i++){
        printf("%f\t%f\n", ((float (*)[terminal_count][2]) mapped_input)[0][i][0],
                ((float (*)[terminal_count][2]) mapped_input)[0][i][1]);
    }
#endif

    int ndata = sizeof(float)*2*terminal_count;  //total size of data

    TF_Tensor *float_tensor = TF_NewTensor(TF_FLOAT, dims, ndims, ((float (*)[terminal_count][2]) mapped_input),
            ndata, &NoOpDeallocator, 0);

#if DEBUG_NN
    if (float_tensor != nullptr)
        printf("TF_NewTensor is OK\n");
    else
        printf("ERROR: Failed TF_NewTensor\n");
#endif

    InputValues[0] = float_tensor;

    return predict();
}

/*
 * CNN
 */

CNN::CNN() {
    // set model dir
    const char *saved_model_dir = "src/ml_integration/model_cnn/model/";
    // init the NN with correct input entry point
    init(saved_model_dir, CNN_ENTRY_POINT);
}

#if DEBUG_NN
float CNN::debug() {
    float tmp[1][CNN_INPUT_GRID_SIZE][CNN_INPUT_GRID_SIZE][1] = {};
    tmp[0][0][0][0] = 1.0f;
    tmp[0][4][2][0] = 1.0f;
    tmp[0][1][5][0] = 1.0f;
    return encode_and_predict(((void*) tmp), 3);
}
#endif

float CNN::preprocess_and_predict(ClusterNetId net_id, t_bb* bbptr, unsigned long number_of_terminals,
                                  const ClusteringContext& cluster_ctx) {

    if(std::max(bbptr->xmax - bbptr->xmin, bbptr->ymax - bbptr->ymin) > CNN_INPUT_GRID_SIZE) // limit exceeded, fall back
        return -1;

    //convert net to grid of relative terminal coords in BB (2d array)

    // auto& device_ctx = g_vpr_ctx.device();
    // auto& grid = device_ctx.grid;
    auto& place_ctx = g_vpr_ctx.placement();

//    if(counter > 186410)
//        printf("creating image: %d\n", counter); // TODO

    // prepare grid (1 image of dimensions CNN_INPUT_GRID_SIZE*CNN_INPUT_GRID_SIZE)
    float image[1][CNN_INPUT_GRID_SIZE][CNN_INPUT_GRID_SIZE][1] = {}; // initialize whole array to 0

//    if(counter > 186410)
//        printf("created image: %d\n", counter); // TODO

    // process source
    ClusterBlockId bnum = cluster_ctx.clb_nlist.net_driver_block(net_id); //source
    int pnum = cluster_ctx.clb_nlist.net_pin_physical_index(net_id, 0);

    int x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
    int y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];

    // float bb_size = std::max(bbptr->xmax - bbptr->xmin, bbptr->ymax - bbptr->ymin);

    image[0][x - bbptr->xmin][y - bbptr->ymin][0] = 1.0f; // set pixel at position of source terminal to 1

    // process sinks
    for(auto pin_id : cluster_ctx.clb_nlist.net_sinks(net_id)) {
        bnum = cluster_ctx.clb_nlist.pin_block(pin_id);
        pnum = cluster_ctx.clb_nlist.pin_physical_index(pin_id);
        x= place_ctx.block_locs[bnum].x + cluster_ctx.clb_nlist.block_type(bnum)->pin_width_offset[pnum];
        y= place_ctx.block_locs[bnum].y + cluster_ctx.clb_nlist.block_type(bnum)->pin_height_offset[pnum];

        image[0][x - bbptr->xmin][y - bbptr->ymin][0] = 1.0f; // set pixel at position of current sink terminal to 1
    }

//    if(counter > 186410) {
//        printf("\n");
//        printf("\n");
        for (int i = 0; i < CNN_INPUT_GRID_SIZE; i++) {
            for (int j = 0; j < CNN_INPUT_GRID_SIZE; j++) {
//                printf("%.0f ", image[0][i][j][0]);
                counter++;
            }
//            printf("\n");
        }
//        printf("\n");
//        printf("\n");
//    }

//    if(counter > 186410)
//        printf("filled image: %d\n", counter); // TODO

    //call predict method
    return encode_and_predict(((void*) image), number_of_terminals);
}

float CNN::encode_and_predict(void* mapped_input, unsigned long terminal_count) {

    int ndims = 3;
    int64_t dims[] = {1, CNN_INPUT_GRID_SIZE, CNN_INPUT_GRID_SIZE, 1};
#if DEBUG_NN
    for(int i = 0; i < CNN_INPUT_GRID_SIZE; i++){
        for(int j = 0; j < CNN_INPUT_GRID_SIZE; j++) {
            printf("%.0f ", ((float (*)[CNN_INPUT_GRID_SIZE][CNN_INPUT_GRID_SIZE][1]) mapped_input)[0][i][j][0]);
        }
        printf("\n");
    }
#endif

    int ndata = sizeof(float)*CNN_INPUT_GRID_SIZE*CNN_INPUT_GRID_SIZE;  //total size of data

    TF_Tensor *float_tensor = TF_NewTensor(TF_FLOAT, dims, ndims,
            ((float (*)[CNN_INPUT_GRID_SIZE][CNN_INPUT_GRID_SIZE][1]) mapped_input), ndata, &NoOpDeallocator,
            0);

//    if(counter > 186410)
//        printf("created tensor: %d\n", counter); // TODO

#if DEBUG_NN
    if (float_tensor != nullptr)
        printf("TF_NewTensor is OK\n");
    else
        printf("ERROR: Failed TF_NewTensor\n");
#endif

    InputValues[0] = float_tensor;

    float raw_prediction = predict();

    TF_DeleteTensor(float_tensor); // TODO

//    if(counter > 186410)
//        printf("predicted successfully: %d\n", counter); // TODO

    return raw_prediction;
}
