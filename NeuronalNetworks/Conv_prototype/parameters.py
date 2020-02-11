NUM_DATA_WORKERS = 8
TRAIN_VAL_TEST_DESCRIPTORS = ["train/", "validate/", "test/"]

batch_size = 250
epochs = 20
loss_function = 'mean_squared_error'
input_file_names = ["out.txt"]  # , "stereovision.txt", "out.txt"]  # ["test.txt"]
optimizer_choice = 'adam'
np_random_seed = 8002
validation_plotting_point_count = 30

# TODO change if the network architecture changes
network_architecture = "Conv(8,(3,3))-Flatten()-Dense(8,relu)-Dense(8,relu)-Dense(4,relu)-Dense(1)"
# Dense(64,relu)-Conv(8,(3,3))
plot_basepath = "plots/" + network_architecture + "/"
data_limit_flag = True
data_limit = 250000

tfrecord_basepath = "records_limited/"
