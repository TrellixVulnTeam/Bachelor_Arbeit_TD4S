import numpy as np
import tensorflow as tf
import os
from parameters import *

with open(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[0]) + "characteristics.txt", "r") as input_file:
    train_dataset_size = int(input_file.readline().split(" ")[0])
    print(train_dataset_size)
    max_grid_size = int(input_file.readline().split(" ")[0])
    print(max_grid_size)

with open(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[1]) + "characteristics.txt", "r") as input_file:
    val_dataset_size = int(input_file.readline().split(" ")[0])
    print(val_dataset_size)

# model definition
model = tf.keras.models.Sequential()

model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), input_shape=(max_grid_size, max_grid_size, 1), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))
#
# model.add(tf.keras.layers.Conv2D(8, kernel_size=(3, 3), activation="relu"))

model.add(tf.keras.layers.Flatten()) # input_shape=(max_grid_size, max_grid_size, 1)))
model.add(tf.keras.layers.Dense(8, activation="relu"))
model.add(tf.keras.layers.Dense(8, activation="relu"))
model.add(tf.keras.layers.Dense(4, activation="relu"))

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


def single_example_parser(tf_example_proto_item):
    feature_values = {
        "mapped_data": tf.io.FixedLenFeature([max_grid_size, max_grid_size, 1], dtype=tf.int64),
        "result": tf.io.FixedLenFeature(shape=(), dtype=tf.int64),
        }

    tensor_data = tf.io.parse_single_example(tf_example_proto_item, feature_values)

    image = tf.cast(tensor_data["mapped_data"], dtype=tf.uint8)

    label = tf.cast(tensor_data["result"], dtype=tf.int32)

    return image, label

# source: https://jkjung-avt.github.io/tfrecords-for-keras/
def get_dataset(tfrecords_dir, local_batch_size):
    """Read TFRecords files and turn them into a TFRecordDataset."""
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


training_dataset = get_dataset(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[0]), batch_size)
validation_dataset = get_dataset(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[1]), batch_size)

history = model.fit(x=training_dataset, validation_data=validation_dataset, epochs=epochs, steps_per_epoch=train_dataset_size, validation_steps=val_dataset_size, callbacks=[tensorboard_cb])
