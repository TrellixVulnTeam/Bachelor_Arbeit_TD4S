# Training Neural Networks

Parameters used by both RNN and CNN training are listed in *parameters.py*

Utility functions for data loading are implemented in *util.py*

## RNNs

For training all predefined models (3 modes, 3 different lstm layer counts, 2 different dense layer counts), simply run *train_model_lstm.py*

To train different configurations either change the parameter domains at the bottom of *train_model_lstm.py*, call *define_model(...)* directly with custom parameters, or specify and compile the model manually, then calling the *fit(...)* method.

#### Custom Model Specification

The model must satisfy following constraints: 

* input shape \[*batch_size*, -1, 2\], 

* final layer: *keras.layers.Dense(1)*

*batch_size* is defined in *parameters.py*

A second model for validation needs to be specified and compiled with the exactly same structure, except for  the input shape.

* validation model input shape: \[1, -1, 2\], i.e. setting a batch size of 1 for this model

## CNNs

Training the CNNs requires preprocessed data saved as tfrecord files.

To change the input dimension of the CNNs, the parameter *cnn_input_grid_size* in *parameters.py* has to be adjusted (grid is always quadratic).

At the same time, the compile-time parameter CNN_INPUT_GRID_SIZE in *ml_integration/neural_network.h* of the modified VPR Placer has to be set to the same value.

#### Data Preparation

To create these tfrecord files holding 1000 samples each, the script *prepare_data_as_pictures.py* has to be executed.

Settings for this process are also located in *parameters.py*:

* cnn_data_hard_limit: cuts the processed data to the first x samples (saves space and speeds up training)

* tfrecord_basepath: path to store the tfrecord files on disk, relative to current directory

#### Training

Training is analogous to RNNs.

However, when defining a custom model, no second model for evaluation is required.

# Creating Plots

Plots are created during training or by running scripts prefixed with *plot\_*.

Results from default training runs or from certain evaluation might be required.

# Evaluating NNs

All tools for model selection and final evaluation are located in the *model_selection/* subfolder. 

This subfolder will be omitted when referring to files in this section.

IMPORTANT: The whole model selection and evaluation process frequently modifies the filesystem in *\[PROJECT_ROOT\]/VPR_PROJECT/vpr/* to deploy NNs and activate the correct mode of VPR. This process is not thread safe. Only one instance of any of these scripts may be run at the same time. The contents of *\[PROJECT_ROOT\]/VPR_PROJECT/vpr/* must not be changed externally during this time.

#### Preparing Trained NNs for Deployment

The script *fix_model_signatures.py* adjusts the signature definition of all saved_models created by the default training procedure to match the ones defined in the modified VPR Placer.

Preparing a single specific saved model can be achieved by modifying *fix_model_signatures.py*, but should not be necessary.

#### Model Selection

Model selection will evaluate the real performance of all trained NNs by integrating each into VPR, determining its runtime factor, and placing the evaluation circuit(s) with adjusted *inner_num* (i.e. with "fixed" runtime).

*util.py* provides utility functions for deploying a NN to VPR and executing the Placer, as well as the definition of the *evaluation* and *test* sets. The circuits in these sets are by default:

* evaluation set: *raygentop*

* test set: *diffeq2*, *or1200*, and *ch_intrinsics*

*model_selection_eval.py* will evaluated all trained NNs stored in the default locations (*../models/rnn* for RNNs and *../models/cnn* for CNNs). It saves the results in the file *runtime_quality_map.pkl*.

To analyze the results and print the best model per type, *plot_model_selection.py* has to be run. 

The best CNN and best RNN model have to be specified manually at the top of *evaluation.py* for the following evaluation.

If a Model has already been evaluated with a certain circuit, the evaluation will simply read the VPR logfiles stored in that model's folder and not call VPR again. To prevent this, the folders prefixed *placement_nr\_* in the model's folder have to be deleted. *runtime\_quality\_map.pkl* should also be deleted.

#### Final Evaluation

Once the best models are specified correctly, the final evaluation can be executed using *evaluation.py*.

If the evaluation presented in the thesis is to be repeated on the same data, no files need to be changed. However, the trained models in *../models/* and the file *runtime_quality_map.pkl* need to be present.

The evaluation will take a long time to finish. 

Intermediary results are saved and terminating and resuming the evaluation is supported 

(IMPORTANT: this process frequently loads and writes data from and to the filesystem. Do not execute any processes that might change the files used by the evaluation, mainly *runtime_quality_map.pkl*, *eval_performance_map.pkl* and the contents of *../models/*.)

As with model selection, repeating the evaluation requires deletion of the saved log files and pickle dump. To do this delete the whole *evaluation\_results* folder as well as the file *eval\_performance\_map.pkl*.

*plot_evaluation.py* visualizes the results and creates a result table in latex format.
