import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt

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

print("input data array:")
print(input_coord_lists)
print("target array:")
print(output_costs)

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
    
print("data sorted by length:")
print("input data:")
print(list_of_batches)
print("output data data:")
print(list_of_batch_target_lists)
print("normalization factors:")
print(list_of_batch_normalization_factor_lists)

print("length of batches:")
for batch in list_of_batches:
    print(len(batch))

batch_size = 1000

for batch_index in range(len(list_of_batches)):
    while len(list_of_batches[batch_index]) % batch_size != 0:
        list_of_batches[batch_index].pop()
        list_of_batch_target_lists[batch_index].pop()
        list_of_batch_normalization_factor_lists[batch_index].pop()
    print(len(list_of_batches[batch_index]))

for batch_index in range(len(list_of_batches)):
    for counter in range(batch_size):
        list_of_batches_validation[batch_index].append(list_of_batches[batch_index].pop())
        list_of_batch_target_lists_validation[batch_index].append(list_of_batch_target_lists[batch_index].pop())
        list_of_batch_normalization_factor_lists_validation[batch_index].append(list_of_batch_normalization_factor_lists[batch_index].pop())


model = tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM(10, batch_input_shape=(batch_size, None, 2), return_sequences=False, stateful=True))
model.add(tf.keras.layers.Dense(1))

model.compile(loss='mean_absolute_error', optimizer='adam', metrics=['accuracy'])
model.summary()

for index in range(len(list_of_batches)):

    # x_train, x_test, y_train, y_test = train_test_split(list_of_batches[index], list_of_batch_target_lists[index], test_size=0.2, random_state=4)

    # x_train = np.asarray(x_train).reshape(len(x_train), 2, 2)
    x_train = np.asarray(list_of_batches[index]).reshape(len(list_of_batches[index]), index + 2, 2)
    y_train = np.asarray(list_of_batch_target_lists[index])
    print(x_train)
    print(len(x_train))
    x_test = np.asarray(list_of_batches_validation[index]).reshape(len(list_of_batches_validation[index]), index + 2, 2)
    y_test = np.asarray(list_of_batch_target_lists_validation[index])
# print(x_train)

    history = model.fit(x_train, y_train, epochs=1000, validation_data=(x_test, y_test))

    results = model.predict(x_test)
    print(results[:, 0].shape)
    print(results.shape)
    print(y_test.shape)
    print(y_test.reshape(len(y_test), 1).shape)
    plt.scatter(range(50), results[:50, 0], c='r')
    plt.scatter(range(50), y_test[:50], c='g')
    plt.show()

    plt.plot(history.history['loss'])
    plt.show()

    model.reset_states()
