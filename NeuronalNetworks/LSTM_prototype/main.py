import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt
import os

# read training and test data from file and format it...
print("started")
input_file = open("test.txt", "r")
lines = input_file.read().splitlines()
input_coord_lists = []
output_costs = []
normalization_factors = []
state = 0
current_normalization_factor = 0

for line in lines:
    if line[0] != '%':
        if state == 0:
            bb_size = line.split(',')
            current_normalization_factor = max(int(bb_size[0]), int(bb_size[1]))
            normalization_factors.append(current_normalization_factor)
            state = 1
        elif state == 1:
            list_of_coord_pairs = line.split(';')
            coord_pair_list = []
            for coord_pair in list_of_coord_pairs:
                x_y_coords = coord_pair.split(',')
                coord_pair_list.append([float(x_y_coords[0]) / current_normalization_factor, float(x_y_coords[1]) / current_normalization_factor])
            input_coord_lists.append(coord_pair_list)
            state = 2
        else:
            output_costs.append(float(line) / current_normalization_factor)
            state = 0

input_file.close()

# data = np.array(input_coord_lists, dtype= float)
# target = np.array(output_costs, dtype= float)

"""
print("input data array:")
print(input_coord_lists)
print("target array:")
print(output_costs)
"""
print("file read,", len(input_coord_lists), "datasets loaded.")

list_of_batches = []
list_of_batch_target_lists = []
list_of_batch_normalization_factor_lists = []
list_of_batches_validation = []
list_of_batch_target_lists_validation = []
list_of_batch_normalization_factor_lists_validation = []

for index in range(len(input_coord_lists)):
    input_data_set = input_coord_lists[index]
    while len(list_of_batches) < len(input_data_set) - 1:
        list_of_batches.append([])
        list_of_batch_target_lists.append([])
        list_of_batch_normalization_factor_lists.append([])

        list_of_batches_validation.append([])
        list_of_batch_target_lists_validation.append([])
        list_of_batch_normalization_factor_lists_validation.append([])

    list_of_batches[len(input_data_set) - 2].append(input_data_set)
    list_of_batch_target_lists[len(input_data_set) - 2].append(output_costs[index])
    list_of_batch_normalization_factor_lists[len(input_data_set) - 2].append(normalization_factors[index])

"""   
print("data sorted by length:")
print("input data:")
print(list_of_batches)
print("output data data:")
print(list_of_batch_target_lists)
print("normalization factors:")
print(list_of_batch_normalization_factor_lists)
"""

print("length of batches:")
i = 0
for batch in list_of_batches:
    if len(batch) == 0:
        break
    print("batch #", i)
    print(len(batch))
    i += 1

batch_size = 250
mini_batch_size = 50
epochs = 64


for batch_index in range(len(list_of_batches)):
    if len(list_of_batches[batch_index]) == 0:
        break
    for counter in range(mini_batch_size):
        list_of_batches_validation[batch_index].append(list_of_batches[batch_index].pop())
        list_of_batch_target_lists_validation[batch_index].append(list_of_batch_target_lists[batch_index].pop())
        list_of_batch_normalization_factor_lists_validation[batch_index].append(list_of_batch_normalization_factor_lists[batch_index].pop())


# remove items until the list contains a multiple of batch_size number of items
for batch_index in range(len(list_of_batches)):
    if len(list_of_batches[batch_index]) == 0:
        break
    while len(list_of_batches[batch_index]) % batch_size != 0:
        list_of_batches[batch_index].pop()
        list_of_batch_target_lists[batch_index].pop()
        list_of_batch_normalization_factor_lists[batch_index].pop()
    print(len(list_of_batches[batch_index]))

# lists containing batches of size batch_size, containing only equally sized input sequences together with their respective normalization factors and expected outputs
batched_data_list = []

for batch_index in range(len(list_of_batches)):
    if len(list_of_batches[batch_index]) == 0:
        break
    for counter in range(int(len(list_of_batches[batch_index]) / batch_size)):
        tmp = [list_of_batches[batch_index][counter * batch_size: (counter+1) * batch_size], list_of_batch_target_lists[batch_index][counter * batch_size: (counter+1) * batch_size], list_of_batch_normalization_factor_lists[batch_index][counter * batch_size: (counter+1) * batch_size], batch_index + 2]
        batched_data_list.append(tmp)


model = tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM(8, batch_input_shape=(mini_batch_size, None, 2), return_sequences=True,))  # stateful=True))
model.add(tf.keras.layers.LSTM(16, return_sequences=True))
model.add(tf.keras.layers.LSTM(20, return_sequences=False))
model.add(tf.keras.layers.Dense(8))
model.add(tf.keras.layers.Dense(1))

"""#Log all variables for Tensorboard
for some_variable in tf.trainable_variables():
    tf.summary.histogram(some_variable.name.replace(":","_"), some_variable)
merged_summary = tf.summary.merge_all()"""

model.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
model.summary()

root_logdir = os.path.join(os.curdir, "my_logs")


def get_run_logdir():
    import time
    run_id = time.strftime("run_%Y_%m_%d-%H_%M_%S")
    return os.path.join(root_logdir, run_id)


run_logdir = get_run_logdir()
tensorboard_cb = tf.keras.callbacks.TensorBoard(run_logdir)

for epoch_count in range(epochs):

    print("epoch #", epoch_count)

    # shuffle the individual batches
    np.random.shuffle(batched_data_list)

    history = []

    for batch_counter in range(len(batched_data_list)):

        print("batch #", batch_counter)

        x_train = np.asarray(batched_data_list[batch_counter][0]).reshape(len(batched_data_list[batch_counter][0]), batched_data_list[batch_counter][3], 2)
        y_train = np.asarray(batched_data_list[batch_counter][1])
        # print(len(x_train))
        # print(len(y_train))
        x_test = np.asarray(list_of_batches_validation[batched_data_list[batch_counter][3] - 2]).reshape(len(list_of_batches_validation[batched_data_list[batch_counter][3] - 2]), batched_data_list[batch_counter][3], 2)
        y_test = np.asarray(list_of_batch_target_lists_validation[batched_data_list[batch_counter][3] - 2])
        # print(x_train)

        model.fit(x_train, y_train, epochs=1, callbacks=[tensorboard_cb])

    # for index in range(len(list_of_batches_validation)):
    x_test = np.asarray(list_of_batches_validation[1]).reshape(len(list_of_batches_validation[1]), 3, 2)
    y_test = np.asarray(list_of_batch_target_lists_validation[1])
    results = model.predict(x_test)
    plt.scatter(range(mini_batch_size), results[:mini_batch_size, 0], c='r')
    plt.scatter(range(mini_batch_size), y_test[:mini_batch_size], c='g')
    plt.show()

    """x_test = np.asarray(list_of_batches_validation[5]).reshape(len(list_of_batches_validation[5]), 7, 2)
    y_test = np.asarray(list_of_batch_target_lists_validation[5])
    results = model.predict(x_test)
    plt.scatter(range(mini_batch_size), results[:mini_batch_size, 0], c='r')
    plt.scatter(range(mini_batch_size), y_test[:mini_batch_size], c='g')
    plt.show()"""

    x_test = np.asarray(list_of_batches_validation[len(list_of_batches_validation) - 1]).reshape(len(list_of_batches_validation[len(list_of_batches_validation) - 1]), len(list_of_batches_validation) - 1 + 2, 2)
    y_test = np.asarray(list_of_batch_target_lists_validation[len(list_of_batches_validation) - 1])
    results = model.predict(x_test)
    plt.scatter(range(mini_batch_size), results[:mini_batch_size, 0], c='r')
    plt.scatter(range(mini_batch_size), y_test[:mini_batch_size], c='g')
    plt.show()

    # plt.plot(history.history['loss'])
    # plt.show()

    # model.reset_states()
