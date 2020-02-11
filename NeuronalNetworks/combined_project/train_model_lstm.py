import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import os
import sys
import math
import gc

from util import *
from parameters import *

# batch_size = 250
# epochs = 32
# loss_function = 'mean_squared_error'
# input_file_names = ["blob_merge.txt"]
# optimizer_choice = 'adam'
# np_random_seed = 8002
# validation_plotting_point_count = 30

# repeatable test runs
np.random.seed(np_random_seed)

# read training and test data from file and format it...
print("started")

# # TODO change if the network architecture changes
# network_architecture = "test-LSTM(8)-LSTM(16)-Dense(1)"
# plot_basepath = "plots/" + network_architecture + "/"
# data_limit_flag = True
# data_limit = 4000

if not os.path.isdir(plot_basepath):
    os.mkdir(plot_basepath)

input_data_set_list = read_input_file_no_duplicates(normalize=True)  # TODO

gc.collect()

print("file read,", len(input_data_set_list), "datasets loaded.")

# shuffle true by default, default random number generator is np.random, seeded above
data_train, data_test = train_test_split(list(input_data_set_list), test_size=(10*int(math.sqrt(len(input_data_set_list)))))
data_train, data_validate = train_test_split(data_train, test_size=(10*int(math.sqrt(len(data_train)))))

print("size of validation set:", len(data_validate))

# "free" list
input_data_set_list = []

# sort training data by length / number of coordinate pairs
list_of_equal_length_data_lists = []
for input_data_set in data_train:
    while len(list_of_equal_length_data_lists) < len(input_data_set.coordinate_pairs) - 1:
        list_of_equal_length_data_lists.append([])
    list_of_equal_length_data_lists[len(input_data_set.coordinate_pairs) - 2].append(input_data_set)
print("data sorted by length.")

# remove datasets of length 2 TODO
list_of_equal_length_data_lists[0] = []

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
# for every distinct length...
for index in range(len(list_of_equal_length_data_lists)):
    # if there are samples of this length...
    if not len(list_of_equal_length_data_lists[index]) == 0:
        # limit number of samples per distinct sequence length to avoid overwhelming number of small samples if flag is set
        if data_limit_flag:
            # for every sequence of length batch size until the maximum number of samples hs been processed do,...
            for counter in range(min(int(data_limit / batch_size), int(len(list_of_equal_length_data_lists[index]) / batch_size))):
                # copy over a consecutive batch to a list of batches
                list_of_batches.append(list_of_equal_length_data_lists[index][counter * batch_size: (counter+1) * batch_size])
        # number of samples per distinct length not limited
        else:
            # for every sequence of length batch size do...
            for counter in range(int(len(list_of_equal_length_data_lists[index]) / batch_size)):
                # copy over a consecutive batch to a list of batches
                list_of_batches.append(list_of_equal_length_data_lists[index][counter * batch_size: (counter+1) * batch_size])

print("size of training data set:", len(list_of_batches), "batches of size", batch_size, ",",
      batch_size * len(list_of_batches), "samples total")

# "free" list
list_of_equal_length_data_lists = []

gc.collect()

# model definition
model = tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM(8, batch_input_shape=(batch_size, None, 2), return_sequences=True,))
model.add(tf.keras.layers.LSTM(16, return_sequences=False))
# model.add(tf.keras.layers.LSTM(20, return_sequences=False))
# model.add(tf.keras.layers.Dense(8))
model.add(tf.keras.layers.Dense(1))

model.compile(loss=loss_function, optimizer=optimizer_choice)
model.summary()

# repeat model definition for a second almost identical model (only difference: batch size of input layer, no
# functional differences, it will produce the same results if the weights are the same)
model_for_validation = tf.keras.models.Sequential()

model_for_validation.add(tf.keras.layers.LSTM(8, batch_input_shape=(1, None, 2), return_sequences=True,))
model_for_validation.add(tf.keras.layers.LSTM(16, return_sequences=False))
# model_for_validation.add(tf.keras.layers.LSTM(20, return_sequences=False))
# model_for_validation.add(tf.keras.layers.Dense(8))
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
    while len(individual_loss_histories) < (len(data.coordinate_pairs) - 1):
        individual_loss_histories.append([[], 0, 0])
    individual_loss_histories[len(data.coordinate_pairs) - 2][1] += 1
final_individual_loss_histories = 0

# history of training loss
history = []

# model epochs
for epoch_count in range(epochs):

    gc.collect()

    print("epoch #", epoch_count)

    # shuffle the individual batches (externally)
    np.random.shuffle(list_of_batches)

    history.append(0)

    # in each epoch train on all the training data, one batch at a time
    for batch_counter in range(len(list_of_batches)):

        print("epoch(" + str(epoch_count) + "/" + str(epochs - 1) + ") batch #", batch_counter)

        # shuffle the specific batch (internally)
        np.random.shuffle(list_of_batches[batch_counter])

        # prepare the data as input to the model
        x_train = np.asarray([data.coordinate_pairs for data in list_of_batches[batch_counter]])
        x_train = x_train.reshape(batch_size, len(list_of_batches[batch_counter][0].coordinate_pairs), 2)
        y_train = np.asarray([data.true_cost for data in list_of_batches[batch_counter]])

        # train on one batch
        history_tmp = model.fit(x_train, y_train, epochs=1)
        history[epoch_count] += history_tmp.history['loss'][0]  # mean squared error can be summed up and later
        # devided by the number of batches, as long as each batch is of equal size

    history[epoch_count] /= len(list_of_batches)  # finalize mean squared error of train run

    # copy weights to the validation model with batch size of 1
    model_for_validation.set_weights(model.get_weights())
    # recompile the model
    model.compile(loss=loss_function, optimizer=optimizer_choice)

    # validate
    produced_results = []
    squared_loss_sum = 0
    # prepare individual loss records
    for individual_loss_list_index in range(len(individual_loss_histories)):
        if not individual_loss_histories[individual_loss_list_index][1] == 0:
            individual_loss_histories[individual_loss_list_index][0].append(0)
    # use the whole validation set
    for data in data_validate:
        result = model_for_validation.predict(np.asarray(data.coordinate_pairs).reshape(1, len(data.coordinate_pairs), 2))
        # log produced results for plotting (only for first, middle and last iteration because of visual clutter)
        if (epoch_count == 0) | (epoch_count == epochs - 1) | (epoch_count == int(epochs / 2)):
            produced_results.append(result)
        # compute validation loss
        if loss_function == 'mean_squared_error':
            squared_error = (result - data.true_cost) * (result - data.true_cost)
            if squared_error > 5:
                print("large error detected:", squared_error)
                print("expected value:", data.true_cost)
                print("computed value:", result)
                print("sequence length:", len(data.coordinate_pairs))
                print("sequence:", data.coordinate_pairs)
            squared_loss_sum += squared_error
            individual_loss_histories[len(data.coordinate_pairs) - 2][0][epoch_count] += squared_error
        else:
            print("ERROR: loss function not implemented")
            sys.exit("failed to compute loss function: not implemented.")
    # log the mean loss for this epoch
    loss_history.append(float(squared_loss_sum / len(data_validate)))
    # finalize individual mean loss values for this epoch
    for individual_loss_list_index in range(len(individual_loss_histories)):
        if not individual_loss_histories[individual_loss_list_index][1] == 0:
            individual_loss_histories[individual_loss_list_index][0][epoch_count] /= individual_loss_histories[individual_loss_list_index][1]

    # compute loss of original bounding box cost for comparison
    squared_original_bb_loss_sum = 0
    if(epoch_count == 0):
        for data in data_validate:
            if loss_function == 'mean_squared_error':
                squared_error = (data.corrected_hpwl - data.true_cost) * (data.corrected_hpwl - data.true_cost)
                squared_original_bb_loss_sum += squared_error
                individual_loss_histories[len(data.coordinate_pairs) - 2][2] += squared_error
            else:
                print("ERROR: loss function not implemented")
                sys.exit("failed to compute loss function: not implemented.")
        # finalize mean loss value of original BB cost
        squared_original_bb_loss_sum /= len(data_validate)
        # finalize individual mean loss values of original BB cost
        for individual_loss_list_index in range(len(individual_loss_histories)):
            if not individual_loss_histories[individual_loss_list_index][1] == 0:
                individual_loss_histories[individual_loss_list_index][2] /= individual_loss_histories[individual_loss_list_index][1]

    # plot expected and produced results (only for first, middle and last iteration because of visual clutter)
    if (epoch_count == 0) | (epoch_count == epochs - 1) | (epoch_count == int(epochs / 2)):
        plt.title("predictions against true values, epoch " + str(epoch_count))
        plt.scatter(range(validation_plotting_point_count),
                    produced_results[:validation_plotting_point_count],
                    c='r')
        plt.scatter(range(validation_plotting_point_count),
                    [data.true_cost for data in data_validate][:validation_plotting_point_count],
                    c='g')
        plt.scatter(range(validation_plotting_point_count),
                    [data.corrected_hpwl for data in data_validate][:validation_plotting_point_count],
                    c='b')
        plt.savefig(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "scatterplot_" +
                    ("initial" if (epoch_count == 0) else ("final" if (epoch_count == epochs - 1) else "midway")) +
                    ".png", bbox_inches='tight')
        plt.show()

    # plot combined validation loss over epochs
    plt.title("loss plot for whole validation data set")
    plt.xlabel("epoch")
    plt.ylabel(loss_function)
    plt.plot(range(epoch_count + 1), loss_history, 'bo-')
    plt.plot(range(epoch_count + 1), history, 'gx-')
    plt.axhline(y=squared_original_bb_loss_sum, color='y', linestyle='-')
    if epoch_count == epochs - 1:
        plt.savefig(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "loss.png", bbox_inches='tight')
    plt.show()

    # plot individual loss histories in one combined plot for easy qualitative comparison at the end
    # if epoch_count == epochs - 1:
    if True:
        # extract only non-empty histories and assign subplot names
        column_names = []
        filtered_individual_loss_histories = []
        filtered_individual_original_loss_histories = []
        for individual_loss_list_index in range(len(individual_loss_histories)):
            if not individual_loss_histories[individual_loss_list_index][1] == 0:
                column_names.append(str(individual_loss_list_index + 2))
                filtered_individual_loss_histories.append(individual_loss_histories[individual_loss_list_index][0])
                individual_original_loss_tmp = []
                for count in range(len(individual_loss_histories[individual_loss_list_index][0])):
                    individual_original_loss_tmp.append(individual_loss_histories[individual_loss_list_index][2])
                filtered_individual_original_loss_histories.append(individual_original_loss_tmp)

        # prepare and print the combined plot
        # prepare data
        df_individual_loss_histories = pd.DataFrame(np.asarray(filtered_individual_loss_histories).reshape(len(filtered_individual_loss_histories), epoch_count + 1).T, columns=np.asarray(column_names))
        df_individual_original_loss_histories = pd.DataFrame(np.asarray(filtered_individual_original_loss_histories).reshape(len(filtered_individual_original_loss_histories), epoch_count + 1).T, columns=np.asarray(column_names))

        print("original BB loss:")
        print(df_individual_original_loss_histories)
        # create plot
        fig1, ax1 = plt.subplots(figsize=(20, 15))
        # assign different colors to different histories
        colors = sns.cubehelix_palette(len(filtered_individual_loss_histories), rot=0.9)
        df_individual_loss_histories.plot(color=colors, ax=ax1, linestyle='-')
        df_individual_original_loss_histories.plot(color=colors, ax=ax1, linestyle='--')
        # generate the legend
        plt.semilogy()
        plt.legend(ncol=4, loc='best')
        # specify title and axis labels
        plt.title("individual loss histories for validation sequences with different lengths")
        plt.xlabel("epoch")
        plt.ylabel(loss_function)
        # if it is the final plot save it (also save a plot just for the initial phase)
        if epoch_count == epochs - 1 or epoch_count == int(epochs / 3):
            final_individual_loss_histories = df_individual_loss_histories
            plt.savefig(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "loss_individual_" + ("final" if (epoch_count == epochs - 1) else "initial") + ".png", bbox_inches='tight')
        # finally make the plot visible
        plt.show()

        print(df_individual_loss_histories)
        print("loss history:")
        print(loss_history)

gc.collect()

with open(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "hyperparameters.txt", "w") as text_file:
    print("network architecture (sequential): {}".format(network_architecture), file=text_file)
    print("batch size: {}".format(batch_size), file=text_file)
    print("number of epochs: {}".format(epochs), file=text_file)
    print("loss function: {}".format(loss_function), file=text_file)
    print("optimizer: {}".format(optimizer_choice), file=text_file)
    print("numpy random number generator seed: {}".format(np_random_seed), file=text_file)
    print("data limit factor: {}".format("none" if not data_limit_flag else data_limit), file=text_file)
with open(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "loss_history.txt", "w") as text_file:
    print("combined validation loss history:", file=text_file)
    print("", file=text_file)
    print(loss_history, file=text_file)
    print("", file=text_file)
    print("individual validation loss histories:", file=text_file)
    print("", file=text_file)
    print(final_individual_loss_histories, file=text_file)
