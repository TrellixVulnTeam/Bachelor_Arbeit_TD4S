import numpy as np
import tensorflow as tf
import os
from parameters import *
import math
from sklearn.model_selection import train_test_split

# repeatable test runs
np.random.seed(np_random_seed)

# read training and test data from file and format it...
print("started")
input_data_set_list = []
state = 0
current_data_set = []


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


lines = []

for filename in input_file_names:
    input_file = open(filename, "r")
    lines.extend(input_file.read().splitlines())
    input_file.close()

print("files read")

for line_number in range(len(lines)):
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
            # if current_data_set[0] < 20:
            input_data_set_list.append(current_data_set)
            current_data_set = []
            state = 0

print("files read,", len(input_data_set_list), "datasets loaded.")

max_grid_size = max(data[0] for data in input_data_set_list) + 1
print("grid size: ", max_grid_size, "x", max_grid_size)

print("shuffle")
np.random.shuffle(input_data_set_list)
print("shuffled data")

# print("input data array:")
# print(input_data_set_list)

# shuffle true by default, default random number generator is np.random, seeded above
data_train, data_test = train_test_split(input_data_set_list, test_size=(10*int(math.sqrt(len(input_data_set_list)))))
data_train, data_validate = train_test_split(data_train, test_size=(10*int(math.sqrt(len(data_train)))))

if not os.path.isdir(tfrecord_basepath):
    os.mkdir(tfrecord_basepath)

for category in TRAIN_VAL_TEST_DESCRIPTORS:

    current_base_path = os.path.join(tfrecord_basepath, category)
    current_data_set_list = []
    if category == TRAIN_VAL_TEST_DESCRIPTORS[0]:
        current_data_set_list = data_train
    elif category == TRAIN_VAL_TEST_DESCRIPTORS[1]:
        current_data_set_list = data_validate
    else:
        current_data_set_list = data_test

    item_counter_in_record = 0
    record_counter = 0
    if not os.path.isdir(current_base_path):
        os.mkdir(current_base_path)
    writer = tf.io.TFRecordWriter(current_base_path + "000.tfrecord")

    hpwl_mse = 0
    pure_hpwl_mse = 0
    average_bb_size = 0
    for dataset in current_data_set_list:
        mapped_data = np.zeros((max_grid_size, max_grid_size), np.uint8)
        for coordinates in dataset[2]:
            mapped_data[coordinates[0]][coordinates[1]] = 1

        item_counter_in_record += 1
        if item_counter_in_record > 1000: # "the recommended number of images stored in one tfrecord file is 1000."
            print(mapped_data)
            item_counter_in_record = 1
            record_counter += 1
            writer.close()
            writer = tf.io.TFRecordWriter(current_base_path + "%.3d.tfrecord" % record_counter)
            print("Creating the %.3d tfrecord file" % record_counter)
        img_raw = mapped_data.flatten()
        example = tf.train.Example(features=tf.train.Features(feature={
            "mapped_data": tf.train.Feature(int64_list=tf.train.Int64List(value=img_raw)),
            "result": tf.train.Feature(int64_list=tf.train.Int64List(value=[dataset[3]]))}))
        writer.write(example.SerializeToString())

        hpwl = get_corrected_bounding_box_cost(dataset[1], len(dataset[2]))
        hpwl_mse += (dataset[3] - hpwl) * (dataset[3] - hpwl)
        pure_hpwl_mse += (dataset[3] - dataset[1]) * (dataset[3] - dataset[1])
        average_bb_size += dataset[0]

    writer.close()
    hpwl_mse /= len(current_data_set_list)
    pure_hpwl_mse /= len(current_data_set_list)
    average_bb_size /= len(current_data_set_list)
    print("hpwl mse: ", hpwl_mse)
    print("pure hpwl mse: ", pure_hpwl_mse)
    print("average bb size: ", average_bb_size)

    with open(current_base_path + "characteristics.txt", "w") as text_file:
        print("{} # size of data set".format(len(current_data_set_list)), file=text_file)
        print("{} # max grid size (dimension of encoded data)".format(max_grid_size), file=text_file)
        print("{} # hpwl mse".format(hpwl_mse), file=text_file)
        print("{} # pure hpwl mse".format(pure_hpwl_mse), file=text_file)
        print("{} # average bb size".format(average_bb_size), file=text_file)
