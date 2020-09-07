from train_model_lstm import *


def train_model_tmp(model: tf.keras.Model, list_of_batches: list,
                current_basepath: str):
    tensorboard_cb = tf.keras.callbacks.TensorBoard(current_basepath, histogram_freq=1)
    x_train = np.asarray([data.coordinate_pairs for data in list_of_batches[0]])
    x_train = x_train.reshape(batch_size, len(list_of_batches[0][0].coordinate_pairs), 2)
    y_train = np.asarray([data.true_cost for data in list_of_batches[0]])
    model.fit(x_train, y_train, epochs=1, callbacks=[tensorboard_cb])


def train_one_model_variant_tmp(lstm_layer_count, dense_layer_count, list_of_batches,
                            data_validate):
    print("\n\n\ntraining model '{}_lstm_layers_{}_dense_layers_{}'\n\n\n".format(
            lstm_layer_count, dense_layer_count, "inflating"
    ))

    current_model = define_model(lstm_layer_count, dense_layer_count, "inflating", False)

    current_basepath = os.path.abspath(
        "./models/tmp/{}_lstm_layers_{}_dense_layers".format(
            lstm_layer_count, dense_layer_count
        )
    )
    train_model_tmp(current_model, list_of_batches, current_basepath)


lstm_layer_counts = [3, 2, 1]
dense_layer_counts = [2, 1]

if __name__ == "__main__":

    # load train data characteristics
    batches, data_val = load_data()

    # HPO loop (grid search over few points because of long runtime)
    for current_lstm_layer_count in lstm_layer_counts:
        for current_dense_layer_count in dense_layer_counts:
            train_one_model_variant_tmp(current_lstm_layer_count, current_dense_layer_count,
                                        batches, data_val)
