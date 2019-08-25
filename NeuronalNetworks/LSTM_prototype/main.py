import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt
import os
import sys
import math

batch_size = 250
epochs = 64
loss_function = 'mean_squared_error'
np_random_seed = 8002
validation_plotting_point_count = 30

# repeatable test runs
np.random.seed(np_random_seed)

# read training and test data from file and format it...
print("started")
input_file = open("out.txt", "r")
lines = input_file.read().splitlines()
input_data_set_list = []
state = 0
current_data_set = []

for line in lines:
    if line[0] != '%':
        if state == 0:
            bb_size = line.split(',')
            current_data_set.append(max(int(bb_size[0]), int(bb_size[1])))
            state = 1
        elif state == 1:
            list_of_coord_pairs = line.split(';')
            coord_pair_list = []
            for coord_pair in list_of_coord_pairs:
                x_y_coords = coord_pair.split(',')
                coord_pair_list.append([float(x_y_coords[0]) / current_data_set[0],
                                        float(x_y_coords[1]) / current_data_set[0]])
            current_data_set.append(coord_pair_list)
            state = 2
        else:
            current_data_set.append(float(line) / current_data_set[0])
            input_data_set_list.append(current_data_set)
            current_data_set = []
            state = 0

input_file.close()

# data = np.array(input_coord_lists, dtype= float)
# target = np.array(output_costs, dtype= float)


# print("input data array:")
# print(input_data_set_list)

print("file read,", len(input_data_set_list), "datasets loaded.")

# shuffle true by default, default random number generator is np.random, seeded above
data_train, data_test = train_test_split(input_data_set_list, test_size=(10*int(math.sqrt(len(input_data_set_list)))))
data_train, data_validate = train_test_split(data_train, test_size=(10*int(math.sqrt(len(data_train)))))

print("size of validation set:", len(data_validate))

# "free" list
input_data_set_list = []

# sort training data by length / number of coordinate pairs
list_of_equal_length_data_lists = []
for index in range(len(data_train)):
    input_data_set = data_train[index][1]
    while len(list_of_equal_length_data_lists) < len(input_data_set) - 1:
        list_of_equal_length_data_lists.append([])
    list_of_equal_length_data_lists[len(input_data_set) - 2].append(data_train[index])
print("data sorted by length.")

# "free" list
data_train = []

# just print stuff
print("number of data sets per feature length:")
for index in range(len(list_of_equal_length_data_lists)):
    if not len(list_of_equal_length_data_lists[index]) == 0:
        print("length", index + 2)
        print(len(list_of_equal_length_data_lists[index]))

# remove items until the list contains a multiple of batch_size number of items
for index in range(len(list_of_equal_length_data_lists)):
    if not len(list_of_equal_length_data_lists[index]) == 0:
        while len(list_of_equal_length_data_lists[index]) % batch_size != 0:
            list_of_equal_length_data_lists[index].pop()
        print(len(list_of_equal_length_data_lists[index]))

# lists containing batches of size batch_size, containing only equally sized input sequences together with their
# respective normalization factors and expected outputs
list_of_batches = []
for index in range(len(list_of_equal_length_data_lists)):
    if not len(list_of_equal_length_data_lists[index]) == 0:
        # for counter in range(min(int(5000 / batch_size), int(len(list_of_equal_length_data_lists[index]) / batch_size))): # TODO
        for counter in range(int(len(list_of_equal_length_data_lists[index]) / batch_size)):  # TODO
            list_of_batches.append(list_of_equal_length_data_lists[index][counter * batch_size: (counter+1) * batch_size])

print("size of training data set:", len(list_of_batches), "batches of size", batch_size, ",",
      batch_size * len(list_of_batches), "samples total")

# "free" list
list_of_equal_length_data_lists = []

# model definition
model = tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM(8, batch_input_shape=(batch_size, None, 2), return_sequences=True,))
model.add(tf.keras.layers.LSTM(16, return_sequences=True))
model.add(tf.keras.layers.LSTM(20, return_sequences=False))
model.add(tf.keras.layers.Dense(8))
model.add(tf.keras.layers.Dense(1))

model.compile(loss=loss_function, optimizer='adam', metrics=['accuracy'])
model.summary()

# repeat model definition for a second almost identical model (only difference: batch size of input layer, no
# functional differences, it will produce the same results if the weights are the same)
model_for_validation = tf.keras.models.Sequential()

model_for_validation.add(tf.keras.layers.LSTM(8, batch_input_shape=(1, None, 2), return_sequences=True,))
model_for_validation.add(tf.keras.layers.LSTM(16, return_sequences=True))
model_for_validation.add(tf.keras.layers.LSTM(20, return_sequences=False))
model_for_validation.add(tf.keras.layers.Dense(8))
model_for_validation.add(tf.keras.layers.Dense(1))

# no tensorboard because of training runs of only 1 epoch each
"""#Log all variables for Tensorboard
for some_variable in tf.trainable_variables():
    tf.summary.histogram(some_variable.name.replace(":","_"), some_variable)
merged_summary = tf.summary.merge_all()

root_logdir = os.path.join(os.curdir, "my_logs")

def get_run_logdir():
    import time
    run_id = time.strftime("run_%Y_%m_%d-%H_%M_%S")
    return os.path.join(root_logdir, run_id)

run_logdir = get_run_logdir()
tensorboard_cb = tf.keras.callbacks.TensorBoard(run_logdir)"""


loss_history = []

# prepare individual loss histories, list contains records of [loss_history, number_of_samples_for_this_feature_length]
individual_loss_histories = []
for data in data_validate:
    while len(individual_loss_histories) < (len(data[1]) - 1):
        individual_loss_histories.append([[], 0])
    individual_loss_histories[len(data[1]) - 2][1] += 1

# model epochs
for epoch_count in range(epochs):

    print("epoch #", epoch_count)

    # shuffle the individual batches (externally)
    np.random.shuffle(list_of_batches)

    history = []

    # in each epoch train on all the training data, one batch at a time
    for batch_counter in range(len(list_of_batches)):

        print("batch #", batch_counter)

        # shuffle the specific batch (internally)
        np.random.shuffle(list_of_batches[batch_counter])

        # prepare the data as input to the model
        x_train = np.asarray([data[1] for data in list_of_batches[batch_counter]])
        x_train = x_train.reshape(batch_size, len(list_of_batches[batch_counter][0][1]), 2)
        y_train = np.asarray([data[2] for data in list_of_batches[batch_counter]])

        # train on one batch
        model.fit(x_train, y_train, epochs=1)

    # copy weights to the validation model with batch size of 1
    model_for_validation.set_weights(model.get_weights())
    # recompile the model
    model.compile(loss=loss_function, optimizer='adam', metrics=['accuracy'])

    # validate
    produced_results = []
    squared_loss_sum = 0
    # prepare individual loss records
    for individual_loss_list_index in range(len(individual_loss_histories)):
        if not individual_loss_histories[individual_loss_list_index][1] == 0:
            individual_loss_histories[individual_loss_list_index][0].append(0)
    # use the whole validation set
    for data in data_validate:
        result = model_for_validation.predict(np.asarray(data[1]).reshape(1, len(data[1]), 2))
        # log produced results for plotting (only for first, middle and last iteration because of visual clutter)
        if (epoch_count == 0) | (epoch_count == epochs - 1) | (epoch_count == int(epochs / 2)):
            produced_results.append(result)
        # compute validation loss
        if loss_function == 'mean_squared_error':
            squared_error = (result - data[2]) * (result - data[2])
            if squared_error > 5:
                print("large error detected:", squared_error)
                print("expected value:", data[2])
                print("computed value:", result)
                print("sequence length:", len(data[1]))
                print("sequence:", data[1])
            squared_loss_sum += squared_error
            individual_loss_histories[len(data[1]) - 2][0][epoch_count] += squared_error
        else:
            print("ERROR: loss function not implemented")
            sys.exit("failed to compute loss function: not implemented.")
    # log the mean loss for this epoch
    loss_history.append(float(squared_loss_sum / len(data_validate)))
    for individual_loss_list_index in range(len(individual_loss_histories)):
        if not individual_loss_histories[individual_loss_list_index][1] == 0:
            individual_loss_histories[individual_loss_list_index][0][epoch_count] /= individual_loss_histories[individual_loss_list_index][1]

    # plot expected and produced results (only for first, middle and last iteration because of visual clutter)
    if (epoch_count == 0) | (epoch_count == epochs - 1) | (epoch_count == int(epochs / 2)):
        plt.title("predictions against true values, epoch " + str(epoch_count))
        plt.scatter(range(validation_plotting_point_count),
                    produced_results[:validation_plotting_point_count],
                    c='r')
        plt.scatter(range(validation_plotting_point_count),
                    [data[2] for data in data_validate][:validation_plotting_point_count],
                    c='g')
        plt.show()

    if epoch_count == epochs - 1:
        for individual_loss_list_index in range(len(individual_loss_histories)):
            if not individual_loss_histories[individual_loss_list_index][1] == 0:
                plt.title("loss plot for validation data of length" + str(individual_loss_list_index + 2))
                plt.xlabel("epoch")
                plt.ylabel(loss_function)
                plt.plot(range(epoch_count + 1), np.asarray(individual_loss_histories[individual_loss_list_index][0]).reshape(len(individual_loss_histories[individual_loss_list_index][0])), 'bx-')
                plt.show()

    # plot loss over epochs
    plt.title("loss plot for whole validation data set")
    plt.xlabel("epoch")
    plt.ylabel(loss_function)
    plt.plot(range(epoch_count + 1), loss_history, 'bo-')
    plt.show()
