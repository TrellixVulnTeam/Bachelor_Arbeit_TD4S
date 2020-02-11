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
from parameters import *

cross_count = [1.0, 1.0, 1.0, 1.0828, 1.1536, 1.2206, 1.2823, 1.3385, 1.3991, 1.4493, 1.4974, 1.5455, 1.5937, 1.6418,
               1.6899, 1.7304, 1.7709, 1.8114, 1.8519, 1.8924, 1.9288, 1.9652, 2.0015, 2.0379, 2.0743, 2.1061, 2.1379,
               2.1698, 2.2016, 2.2334, 2.2646, 2.2958, 2.3271, 2.3583, 2.3895, 2.4187, 2.4479, 2.4772, 2.5064, 2.5356,
               2.5610, 2.5864, 2.6117, 2.6371, 2.6625, 2.6887, 2.7148, 2.7410, 2.7671, 2.7933]


def get_corrected_bounding_box_cost(bb_cost, number_of_terminals):
    "this computes the crossing value for the net and applies it to the bounding box cost to correct cost of large nets, code taken from VTR placer"
    if number_of_terminals > 50 & number_of_terminals < 85:
        crossing = 2.7933 + 0.02616 * (number_of_terminals - 50)
    else:
        if number_of_terminals >= 85:
            crossing = 2.7933 + 0.011 * number_of_terminals - 0.0000018 * number_of_terminals * number_of_terminals
        else:
            crossing = cross_count[number_of_terminals - 1]

    return bb_cost * crossing


# repeatable test runs
np.random.seed(np_random_seed)

# read training and test data from file and format it...
print("started")
input_data_set_list = []
state = 0
current_data_set = []

if not os.path.isdir(plot_basepath):
    os.mkdir(plot_basepath)

for filename in input_file_names:
    input_file = open(filename, "r")
    lines = input_file.read().splitlines()

    for line_number in range(len(lines)):
        if line_number % 50000 == 0:
            gc.collect()
        line = lines[line_number]
        if line[0] != '%':
            if state == 0:
                bb_size = line.split(',')
                current_data_set.append(max(int(bb_size[0]), int(bb_size[1])))
                current_data_set.append(int(bb_size[0]) + int(bb_size[1]))
                state = 1
            elif state == 1:
                list_of_coord_pairs = line.split(';')
                coord_pair_list = []
                for coord_pair in list_of_coord_pairs:
                    x_y_coords = coord_pair.split(',')
                    coord_pair_list.append([int(x_y_coords[0]),
                                            int(x_y_coords[1])])
                current_data_set.append(coord_pair_list)
                current_data_set[1] = get_corrected_bounding_box_cost(current_data_set[1], len(coord_pair_list)) / current_data_set[0]
                state = 2
            else:
                current_data_set.append(int(line))
                if current_data_set[0] < 20:
                    input_data_set_list.append(current_data_set)
                current_data_set = []
                state = 0

    if data_limit_flag & len(input_data_set_list) >= data_limit:
        break

    input_file.close()
    gc.collect()

# data = np.array(input_coord_lists, dtype= float)
# target = np.array(output_costs, dtype= float)

max_grid_size = max(data[0] for data in input_data_set_list) + 1
print("grid size: ", max_grid_size, "x", max_grid_size)

# print("input data array:")
# print(input_data_set_list)

print("file read,", len(input_data_set_list), "datasets loaded.")

# shuffle true by default, default random number generator is np.random, seeded above
data_train, data_test = train_test_split(input_data_set_list, test_size=(10*int(math.sqrt(len(input_data_set_list)))))

X = []
y = []
hpwl_mse = 0
pure_hpwl_mse = 0
average_bb_size = 0
for dataset in data_train:
    mapped_data = np.zeros((max_grid_size, max_grid_size), int)
    for coordinates in dataset[2]:
        mapped_data[coordinates[0]][coordinates[1]] = 1
    X.append(mapped_data)
    y.append(dataset[3])
    hpwl = get_corrected_bounding_box_cost(dataset[1], len(dataset[2]))
    hpwl_mse += (dataset[3] - hpwl) * (dataset[3] - hpwl)
    pure_hpwl_mse += (dataset[3] - dataset[1]) * (dataset[3] - dataset[1])
    average_bb_size += dataset[0]

hpwl_mse /= len(data_train)
pure_hpwl_mse /= len(data_train)
average_bb_size /= len(data_train)
print("hpwl mse: ", hpwl_mse)
print("pure hpwl mse: ", pure_hpwl_mse)
print("average bb size: ", average_bb_size)

print(np.asarray(X).shape)
print(np.asarray(X).shape[1:])

# "free" list
input_data_set_list = []

# model definition
model = tf.keras.models.Sequential()

model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), input_shape=(max_grid_size, max_grid_size, 1), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))

model.add(tf.keras.layers.Flatten())# input_shape=(max_grid_size, max_grid_size, 1)))
model.add(tf.keras.layers.Dense(8, activation="relu"))
model.add(tf.keras.layers.Dense(8, activation="relu"))
# model.add(tf.keras.layers.Dense(8, activation="relu"))

model.add(tf.keras.layers.Dense(1))

model.compile(loss=loss_function, optimizer=optimizer_choice, metrics=[loss_function])
model.summary()

# Log all variables for Tensorboard
"""for some_variable in tf.trainable_variables():
    tf.summary.histogram(some_variable.name.replace(":","_"), some_variable)
merged_summary = tf.summary.merge_all()"""

root_logdir = os.path.join(os.curdir, "my_logs")


def get_run_logdir():
    import time
    run_id = time.strftime(network_architecture + "run_%Y_%m_%d-%H_%M_%S")
    return os.path.join(root_logdir, run_id)


run_logdir = get_run_logdir()
tensorboard_cb = tf.keras.callbacks.TensorBoard(run_logdir, histogram_freq=1)


history = model.fit(np.asarray(X).reshape(len(X), max_grid_size, max_grid_size, 1), np.asarray(y), epochs=epochs, batch_size=batch_size, validation_split=0.1, callbacks=[tensorboard_cb])

print("hpwl mse: ", hpwl_mse)
print("pure hpwl mse: ", pure_hpwl_mse)
print("average bb size: ", average_bb_size)

with open(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "hyperparameters.txt", "w") as text_file:
    print("network architecture (sequential): {}".format(network_architecture), file=text_file)
    print("batch size: {}".format(batch_size), file=text_file)
    print("number of epochs: {}".format(epochs), file=text_file)
    print("loss function: {}".format(loss_function), file=text_file)
    print("optimizer: {}".format(optimizer_choice), file=text_file)
    print("numpy random number generator seed: {}".format(np_random_seed), file=text_file)
    print("data limit factor: {}".format("none" if not data_limit_flag else data_limit), file=text_file)
