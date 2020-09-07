from util import *


def define_model(conv_layer_count: int, inflation_type: str, conv_kernel_size: int) -> tf.keras.Model:
    """
    define and compile a keras model based on the given parameters
    :param conv_layer_count: number of convolutional layers, including input layer
    :param inflation_type: the distribution of neurons over the model: one of
        'inflating': starting with 4 neurons in input layer, every subsequent layer has 4 additional neurons
        'deflating': every subsequent layer has 4 neurons less than the preceding layer, ending with 4 neurons in the
                     layer immediately before the final dense layer
        the final dense layer always has 1 neuron.
    :param conv_kernel_size: size of the kernel of all convolutional layers
    :return: the compiled model
    """

    filter_count = 4 if inflation_type == "deflating" else 1

    # model definition
    model = tf.keras.models.Sequential()

    if conv_layer_count > 0:

        # input layer
        model.add(tf.keras.layers.Conv2D(filters=filter_count, kernel_size=conv_kernel_size,
                                         input_shape=(cnn_input_grid_size, cnn_input_grid_size, 1), activation="relu"))

        # hidden layers
        for _ in range(conv_layer_count - 1):
            # update filter count according to mode
            filter_count = filter_count // 2 if inflation_type == "deflating" else filter_count * 2
            # add additional conv layer
            model.add(tf.keras.layers.Conv2D(filters=filter_count, kernel_size=conv_kernel_size, activation="relu"))

        model.add(tf.keras.layers.Flatten())

    else:
        # input layer
        model.add(tf.keras.layers.Flatten(input_shape=(cnn_input_grid_size, cnn_input_grid_size, 1)))

    # last hidden layer
    model.add(tf.keras.layers.Dense(4 if inflation_type == "deflating" else 16, activation="relu"))

    # output layer
    model.add(tf.keras.layers.Dense(1))

    # compile model and print structural info
    model.compile(loss=loss_function, optimizer=optimizer_choice, metrics=[loss_function])
    model.summary()

    return model


def train_model(model: tf.keras.Model, basepath: str) -> tf.keras.Model:
    """
    trains the given model with early stopping, saving tensorboard logs in the given directory
    :param model: the model to train
    :param basepath: directory to save the tensorboard logs and the checkpoints in
    :return: the trained model
    """

    run_logdir = os.path.abspath(os.path.join(basepath, "logs"))
    # initialize tensorboard with log directory
    tensorboard_cb = tf.keras.callbacks.TensorBoard(run_logdir, histogram_freq=1)

    # define early stopping and checkpointing callbacks
    es = tf.keras.callbacks.EarlyStopping(monitor='val_loss', mode='min', verbose=1, patience=early_stopping_patience)
    checkpoint_filepath = os.path.abspath(os.path.join(basepath, 'best_model.h5'))
    mc = tf.keras.callbacks.ModelCheckpoint(
        checkpoint_filepath,
        monitor='val_loss', mode='min', verbose=1, save_weights_only=True, save_best_only=True
    )

    # prepare train and evaluation data generators
    training_dataset = get_dataset(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[0]), batch_size)
    validation_dataset = get_dataset(os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[1]), batch_size)

    # train the model
    model.fit(x=training_dataset, validation_data=validation_dataset, epochs=epochs,
              steps_per_epoch=train_dataset_size, validation_steps=val_dataset_size,
              callbacks=[tensorboard_cb, es, mc])

    # restore weights of best checkpoint
    model.load_weights(checkpoint_filepath)

    return model


def train_one_model_variant(conv_layer_count, inflation_type, conv_kernel_size):
    """
    creates a model based on teh given parameters and trains it, saving it to disk
    :param conv_layer_count: number of convolutional layers
    :param inflation_type: the distribution of neurons over the model: one of
        'inflating': starting with 4 neurons in input layer, every subsequent layer has 4 additional neurons
        'deflating': every subsequent layer has 4 neurons less than the preceding layer, ending with 4 neurons in the
                     layer immediately before the final dense layer
        the final dense layer always has 1 neuron.
    :param conv_kernel_size: size of the kernel of all convolutional layers
    :return: nothing, modifies filesystem
    """
    print("\n\n\ntraining model '{}_conv_layers_{}_kernel_size_{}'\n\n\n".format(
        conv_layer_count, inflation_type, conv_kernel_size
    ))
    # define teh model
    current_model = define_model(conv_layer_count, inflation_type, conv_kernel_size)
    # prepare path to save model and logs/plots
    current_basepath = os.path.abspath(
        "./models/conv/{}_conv_layers_{}_kernel_size_{}".format(
            conv_layer_count, inflation_type, conv_kernel_size
        )
    )
    # train the model
    current_model = train_model(current_model, current_basepath)
    # save the model to disk for deployment
    current_model.save(os.path.abspath(os.path.join(current_basepath, "model")), include_optimizer=False)


conv_layer_counts = [2, 1, 0]
conv_kernel_sizes = [7, 3]
inflation_types = ["inflating", "deflating"]

if __name__ == "__main__":
    # load train data characteristics
    with open(
            os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[0]) + "characteristics.txt", "r"
    ) as input_file:
        train_dataset_size = int(input_file.readline().split(" ")[0])
        print("size of training set: {} samples".format(train_dataset_size))
        max_grid_size = int(input_file.readline().split(" ")[0])
        print("maximum occurring BB size: {}x{}".format(max_grid_size, max_grid_size))

    # load validation data characteristics
    with open(
            os.path.join(tfrecord_basepath, TRAIN_VAL_TEST_DESCRIPTORS[1]) + "characteristics.txt", "r"
    ) as input_file:
        val_dataset_size = int(input_file.readline().split(" ")[0])
        print("size of validation set: {} samples".format(val_dataset_size))

    # HPO loop (grid search over few points because of long runtime)
    for current_conv_layer_count in conv_layer_counts:
        for current_inflation_type in inflation_types:
            if current_conv_layer_count > 0:
                for current_conv_kernel_size in conv_kernel_sizes:
                    train_one_model_variant(current_conv_layer_count, current_inflation_type, current_conv_kernel_size)
            else:
                train_one_model_variant(current_conv_layer_count, current_inflation_type, -1)

