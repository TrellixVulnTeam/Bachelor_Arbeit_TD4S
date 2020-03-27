NUM_DATA_WORKERS = 8
TRAIN_VAL_TEST_DESCRIPTORS = ["train/", "validate/", "test/"]

batch_size = 500
epochs = 10
loss_function = 'mean_squared_error'
input_file_names = ["stereovision.txt"]  # , "stereovision.txt", "out.txt"]  # ["test.txt"]
optimizer_choice = 'adam'
np_random_seed = 8072  # 8002
validation_plotting_point_count = 30

# TODO change if the network architecture changes
network_architecture = "LSTM(4)-LSTM(8)-Dense(4)-Dense(1)"  # "Conv(8,(3,3))-Flatten()-Dense(8,relu)-Dense(8,relu)-Dense(4,relu)-Dense(1)"
# Dense(64,relu)-Conv(8,(3,3))
plot_basepath = "plots/" + network_architecture + "/"
data_limit_flag = True
data_limit = 4000

tfrecord_basepath = "records_limited/"

print_high_error_samples = False
print_and_plot_stats_every_epoch = False
compute_and_plot_reference_train_error = False
