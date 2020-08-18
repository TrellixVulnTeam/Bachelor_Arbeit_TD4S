from parameters import *

import os
import tensorflow as tf

cross_count = [1.0, 1.0, 1.0, 1.0828, 1.1536, 1.2206, 1.2823, 1.3385, 1.3991, 1.4493, 1.4974, 1.5455, 1.5937, 1.6418,
               1.6899, 1.7304, 1.7709, 1.8114, 1.8519, 1.8924, 1.9288, 1.9652, 2.0015, 2.0379, 2.0743, 2.1061, 2.1379,
               2.1698, 2.2016, 2.2334, 2.2646, 2.2958, 2.3271, 2.3583, 2.3895, 2.4187, 2.4479, 2.4772, 2.5064, 2.5356,
               2.5610, 2.5864, 2.6117, 2.6371, 2.6625, 2.6887, 2.7148, 2.7410, 2.7671, 2.7933]


class SingleDataSet(object):
    """
    defines a class to enable custom equality check and set building only depending on the coordinate pairs
    """
    def __init__(self, max_of_bb_size, corrected_hpwl, coordinate_pairs, true_cost):
        self.max_of_bb_size = max_of_bb_size
        self.corrected_hpwl = corrected_hpwl
        self.coordinate_pairs = coordinate_pairs
        self.true_cost = true_cost

    def __eq__(self, other):
        return self.coordinate_pairs == other.coordinate_pairs

    def __hash__(self):
        return hash(str(self.coordinate_pairs))  # ugly, but hey, it works...

    def __str__(self):
        return "bb_max: {}, hpwl: {}, true_cost: {},\ncoord_pairs: {}\n\n".format(
            self.max_of_bb_size, self.corrected_hpwl, self.true_cost, self.coordinate_pairs)

    def __repr__(self):
        return self.__str__()


def get_corrected_bounding_box_cost(bb_cost, number_of_terminals):
    """
    this computes the crossing value for the net and applies it to the bounding box cost to correct cost of large nets,
    code taken from VTR placer
    :param bb_cost: the uncorrected bounding box cost
    :param number_of_terminals: the number of terminals in the net
    :return: the corrected bounding box cost
    """
    if number_of_terminals > 50 & number_of_terminals < 85:
        crossing = 2.7933 + 0.02616 * (number_of_terminals - 50)
    else:
        if number_of_terminals >= 85:
            crossing = 2.7933 + 0.011 * number_of_terminals - 0.0000018 * number_of_terminals * number_of_terminals
        else:
            crossing = cross_count[number_of_terminals - 1]

    return bb_cost * crossing


def read_input_file(normalize, respect_ordering=True, remove_len_2_and_3=True):
    """
    TODO
    :return:
    """
    input_data_set_list = []
    state = 0
    current_data_set = []

    lines = []

    for filename in input_file_names:
        input_file = open("./input_files/" + filename, "r")
        lines.extend(input_file.read().splitlines())
        input_file.close()

    print("files read, processing input...")

    for line_number in range(len(lines)):
        line = lines[line_number]
        if line[0] != '%':
            if state == 0:  # first line of single dataset in input file: bounding box size as '[x_size],[y_size]'
                bb_size = line.split(',')
                current_data_set.append(max(int(bb_size[0]), int(bb_size[1])))  # first element: max of bounding box
                # dimensions
                current_data_set.append(int(bb_size[0]) + int(bb_size[1]))  # second element (for now): pure HPWL
                state = 1  # iterate state counter
            elif state == 1:  # first line of single dataset in input file: terminal coordinates as 'x1,y1;...;xn,yn'
                list_of_coord_pairs = line.split(';')
                coord_pair_list = []
                for coord_pair in list_of_coord_pairs:
                    x_y_coords = coord_pair.split(',')
                    if normalize:
                        coord_pair_list.append([int(x_y_coords[0]) / current_data_set[0],
                                                int(x_y_coords[1]) / current_data_set[0]])
                    else:
                        coord_pair_list.append([int(x_y_coords[0]),
                                                int(x_y_coords[1])])
                if respect_ordering:
                    current_data_set.append(coord_pair_list)  # third element: list of coordinate pairs
                else:
                    coord_pair_list.sort()  # sorts coordinate pairs in ascending order, first by X, then by Y
                    current_data_set.append(coord_pair_list)  # third element: list of coordinate pairs
                if normalize:  # TODO
                    current_data_set[1] = (
                                        get_corrected_bounding_box_cost(current_data_set[1], len(coord_pair_list))
                                        /
                                        current_data_set[0]
                                    )  # second element: normalized corrected HPWL
                else:
                    current_data_set[1] = get_corrected_bounding_box_cost(current_data_set[1], len(coord_pair_list))
                    # second element: corrected HPWL
                state = 2  # iterate state counter
            else:
                if normalize:
                    current_data_set.append(int(line) / current_data_set[0])  # fourth element: normalized "real"
                    # cost computed by vpr router
                else:
                    current_data_set.append(int(line))  # fourth element: "real" cost computed by vpr router
                # if current_data_set[0] < 20:
                if (not remove_len_2_and_3) or (len(current_data_set[2]) >= 4):
                    input_data_set_list.append(
                        SingleDataSet(
                            current_data_set[0],
                            current_data_set[1],
                            current_data_set[2],
                            current_data_set[3]
                        )
                    )  # add finished dataset to list
                current_data_set = []  # reset
                state = 0  # reset

    print("files read,", len(input_data_set_list), "datasets loaded.")

    return input_data_set_list


def read_input_file_no_duplicates(normalize, respect_ordering=True, remove_len_2_and_3=True):
    input_data_set_list = read_input_file(normalize, respect_ordering, remove_len_2_and_3)
    return set(input_data_set_list)


def single_example_parser(tf_example_proto_item):
    """
    converts a tensorflow "proto item" (format of one sample inside tfrecords) back into plain sample
    :param tf_example_proto_item: the encoded sample to convert
    :return: X and y of the sample
    """
    # define encoding format (matches the one used when creating the tfrecord files)
    feature_values = {
        "mapped_data": tf.io.FixedLenFeature([cnn_input_grid_size, cnn_input_grid_size, 1], dtype=tf.int64),
        "result": tf.io.FixedLenFeature(shape=(), dtype=tf.int64),
    }
    # parse the example
    tensor_data = tf.io.parse_single_example(tf_example_proto_item, feature_values)
    # convert X to uint8 image
    image = tf.cast(tensor_data["mapped_data"], dtype=tf.uint8)
    # convert y to int32 cost value
    label = tf.cast(tensor_data["result"], dtype=tf.int32)
    # return X and y
    return image, label


# define data generator to load samples from disk on demand
# source: https://jkjung-avt.github.io/tfrecords-for-keras/
def get_dataset(tfrecords_dir, local_batch_size):
    """
    Read TFRecords files and turn them into a TFRecordDataset.
    :param tfrecords_dir: path to directory where the tfrecord files are stored
    :param local_batch_size: batch size to be used for training
    :return: the data generator
    """
    files = tf.io.matching_files(os.path.join(tfrecords_dir, '*.tfrecord'))
    shards = tf.data.Dataset.from_tensor_slices(files)
    # shards = shards.shuffle(tf.cast(tf.shape(files)[0], tf.int64))
    shards = shards.repeat()
    dataset = shards.interleave(tf.data.TFRecordDataset, cycle_length=4)
    dataset = dataset.shuffle(buffer_size=8192)
    dataset = dataset.map(map_func=single_example_parser, num_parallel_calls=NUM_DATA_WORKERS)
    dataset = dataset.batch(batch_size=local_batch_size)
    dataset = dataset.prefetch(batch_size)
    return dataset
