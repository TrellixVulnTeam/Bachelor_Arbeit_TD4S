import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt

# read training and test data from file and format it...
input_file = open("training_data.txt", "r")
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

# data = np.array(input_coord_lists, dtype= float)
# target = np.array(output_costs, dtype= float)

print("input data array:")
print(input_coord_lists)
print("target array:")
print(output_costs)

# Data = [[[(i+j)/100] for i in range(5)] for j in range(100)]
# target = [((i+5)/100) for i in range(100)]
# data = np.array(Data, dtype= float)
# target= np.array(target, dtype= float)

x_train, x_test, y_train, y_test = train_test_split(input_coord_lists, output_costs, test_size=0.2, random_state=4)

# print(x_train)

model = tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM(1, batch_input_shape=(None, None, 2), return_sequences=False))

model.compile(loss='mean_absolute_error', optimizer='adam', metrics=['accuracy'])
model.summary()

history = model.fit(x_train, y_train, epochs=800, validation_data=(x_test, y_test))

results = model.predict(x_test)

plt.scatter(range(20), results, c='r')
plt.scatter(range(20), y_test, c='g')
plt.show()

plt.plot(history.history['loss'])
plt.show()
