import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt

Data = [[[(i+j)/100] for i in range(5)] for j in range(100)]
target = [((i+5)/100) for i in range(100)]
data = np.array(Data, dtype= float)
target= np.array(target, dtype= float)

x_train,x_test,y_train, y_test= train_test_split(data,target,test_size= 0.2, random_state= 4)

model= tf.keras.models.Sequential()

model.add(tf.keras.layers.LSTM((1), batch_input_shape= (None, 5, 1), return_sequences= False))

model.compile(loss= 'mean_absolute_error', optimizer= 'adam', metrics= ['accuracy'])
model.summary()

history=model.fit(x_train, y_train, epochs= 800, validation_data=(x_test, y_test))

results= model.predict(x_test)

plt.scatter(range(20), results, c= 'r')
plt.scatter(range(20), y_test, c= 'g')
plt.show()

plt.plot(history.history['loss'])
plt.show()