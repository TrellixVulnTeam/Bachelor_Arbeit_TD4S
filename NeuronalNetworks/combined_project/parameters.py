#
# general
#

"""
training batch size
"""
batch_size = 500
"""
number of epochs for training
"""
epochs = 25
"""
training loss function
"""
loss_function = 'mean_squared_error'
"""
training data source files
"""
input_file_names = ["stereovision.txt"]  # , "blob_merge.txt"]
"""
optimizer for training
"""
optimizer_choice = 'adam'
"""
numpy random seed for repeatable runs
"""
np_random_seed = 8072  # 8002
"""
Patience setting for early stopping: stop training if no improvement for x epochs
"""
early_stopping_patience = 4

#
# RNN training
#

"""
number of samples to plot when training RNNs
"""
validation_plotting_point_count = 30
"""
Flag whether to limit number of samples with a unique terminal count
"""
data_limit_flag = True
"""
number of samples per distinct terminal count allowed, only used if data_limit_flag == True
"""
data_limit = 4000
"""
Flag whether to print info when sample produces high prediction error during RNN training
"""
print_high_error_samples = False
"""
Flag whether to plot various plots every epoch during RNN training
"""
print_and_plot_stats_every_epoch = False
"""
Flag whether to to compute 'reference train error' after each epoch during RNN training. 
This option slows down training considerably.
"""
compute_and_plot_reference_train_error = False

#
# CNN training
#

"""
path to store tfrecord files holding preprocessed training samples, relative to current directory
"""
tfrecord_basepath = "records_limited/"
"""
descriptors for training, validation and test datasets, used as subfolder names to store tfrecord files in
"""
TRAIN_VAL_TEST_DESCRIPTORS = ["train/", "validate/", "test/"]
"""
number of threads used to load data from tfrecord files during training
"""
NUM_DATA_WORKERS = 8
"""
size of cnn input samples in pixels (quadratic images). supports net placements with BB up to this size
"""
cnn_input_grid_size = 64
"""
hard limit for number of samples used for CNN training. Use only first x samples of shuffled list of loaded samples.
"""
cnn_data_hard_limit = 20000
