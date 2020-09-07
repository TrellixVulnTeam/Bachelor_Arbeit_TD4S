import numpy as np
import tensorflow as tf
import os
from parameters import *
from util import *
import math
from sklearn.model_selection import train_test_split


if __name__ == "__main__":
    # repeatable test runs
    np.random.seed(np_random_seed)

    print("started")

    # read training and test data from file and format it...
    # eliminates duplicates, both direct ones and same coords with different orderings
    input_data_set_list = list(read_input_file_no_duplicates(normalize=False, respect_ordering=False))

    max_grid_size = max(data.max_of_bb_size for data in input_data_set_list) + 1
    print("maximum bb size: {}x{}".format(max_grid_size, max_grid_size))
    print("grid size: {}x{}".format(cnn_input_grid_size, cnn_input_grid_size))

    print("shuffling data...")
    np.random.shuffle(input_data_set_list)
    print("shuffled data")

    print("additionally limiting data to achieve acceptable training duration...")
    input_data_set_list = input_data_set_list[:cnn_data_hard_limit]
    print("limited data to {} samples (including train, val and test set.".format(cnn_data_hard_limit))

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
            mapped_data = np.zeros((cnn_input_grid_size, cnn_input_grid_size), np.uint8)
            for coordinates in dataset.coordinate_pairs:
                mapped_data[coordinates[0]][coordinates[1]] = 1

            item_counter_in_record += 1
            if item_counter_in_record > 1000:  # "the recommended number of images stored in one tfrecord file is 1000."
                print(mapped_data)
                item_counter_in_record = 1
                record_counter += 1
                writer.close()
                writer = tf.io.TFRecordWriter(current_base_path + "%.3d.tfrecord" % record_counter)
                print("Creating the %.3d tfrecord file" % record_counter)
            img_raw = mapped_data.flatten()
            example = tf.train.Example(features=tf.train.Features(feature={
                "mapped_data": tf.train.Feature(int64_list=tf.train.Int64List(value=img_raw)),
                "result": tf.train.Feature(int64_list=tf.train.Int64List(value=[dataset.true_cost]))}))
            writer.write(example.SerializeToString())

            hpwl = get_corrected_bounding_box_cost(dataset.corrected_hpwl, len(dataset.coordinate_pairs))
            hpwl_mse += (dataset.true_cost - hpwl) * (dataset.true_cost - hpwl)
            pure_hpwl_mse += (dataset.true_cost - dataset.corrected_hpwl) * \
                             (dataset.true_cost - dataset.corrected_hpwl)
            average_bb_size += dataset.max_of_bb_size

        writer.close()
        hpwl_mse /= len(current_data_set_list)
        pure_hpwl_mse /= len(current_data_set_list)
        average_bb_size /= len(current_data_set_list)
        print("hpwl mse: ", hpwl_mse)
        print("pure hpwl mse: ", pure_hpwl_mse)
        print("average bb size: ", average_bb_size)

        with open(current_base_path + "characteristics.txt", "w") as text_file:
            print("{} # size of data set".format(len(current_data_set_list)), file=text_file)
            print("{} # max occurring bb size".format(max_grid_size), file=text_file)
            print("{} # grid size limit (dimension of encoded data)".format(cnn_input_grid_size), file=text_file)
            print("{} # hpwl mse".format(hpwl_mse), file=text_file)
            print("{} # pure hpwl mse".format(pure_hpwl_mse), file=text_file)
            print("{} # average bb size".format(average_bb_size), file=text_file)
