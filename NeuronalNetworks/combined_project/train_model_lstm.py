from util import *
from parameters import *

import numpy as np

# repeatable test runs, seed before importing tensorflow
np.random.seed(np_random_seed)

from sklearn.model_selection import train_test_split
import tensorflow as tf
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import os
import sys
import math
import gc


def load_data():
    # read training and test data from file and format it...
    print("started")

    input_data_set_list = read_input_file_no_duplicates(normalize=True, remove_len_2_and_3=True)

    gc.collect()

    print("file read,", len(input_data_set_list), "datasets loaded.")

    # shuffle true by default, default random number generator is np.random, seeded above
    data_train, data_test = train_test_split(
        list(input_data_set_list), test_size=(10*int(math.sqrt(len(input_data_set_list))))
    )
    data_train, data_validate = train_test_split(data_train, test_size=(10*int(math.sqrt(len(data_train)))))

    print("size of validation set:", len(data_validate))
    # "free" list
    input_data_set_list = []
    # sort training data by length / number of coordinate pairs
    list_of_equal_length_data_lists = []
    for input_data_set in data_train:
        while len(list_of_equal_length_data_lists) < len(input_data_set.coordinate_pairs) - 1:
            list_of_equal_length_data_lists.append([])
        list_of_equal_length_data_lists[len(input_data_set.coordinate_pairs) - 2].append(input_data_set)
    print("data sorted by length.")
    # "free" list
    data_train = []
    # just print stuff
    print("number of data sets per feature length:")
    for index in range(len(list_of_equal_length_data_lists)):
        if not len(list_of_equal_length_data_lists[index]) == 0:
            print("length", index + 2)
            print(len(list_of_equal_length_data_lists[index]))
    # remove items until the list contains a multiple of batch_size number of items
    for index in range(len(list_of_equal_length_data_lists)):
        if not len(list_of_equal_length_data_lists[index]) == 0:
            while len(list_of_equal_length_data_lists[index]) % batch_size != 0:
                list_of_equal_length_data_lists[index].pop()
            print(len(list_of_equal_length_data_lists[index]))
    # lists containing batches of size batch_size, containing only equally sized input sequences together with their
    # respective normalization factors and expected outputs
    list_of_batches = []
    # for every distinct length...
    for index in range(len(list_of_equal_length_data_lists)):
        # if there are samples of this length...
        if not len(list_of_equal_length_data_lists[index]) == 0:
            # limit number of samples per distinct sequence length to avoid overwhelming number of small samples if flag
            # is set
            if data_limit_flag:
                # for every sequence of length batch size until the maximum number of samples hs been processed do,...
                for counter in range(
                        min(int(data_limit / batch_size), int(len(list_of_equal_length_data_lists[index]) / batch_size))
                ):
                    # copy over a consecutive batch to a list of batches
                    list_of_batches.append(
                        list_of_equal_length_data_lists[index][counter * batch_size: (counter+1) * batch_size]
                    )
            # number of samples per distinct length not limited
            else:
                # for every sequence of length batch size do...
                for counter in range(int(len(list_of_equal_length_data_lists[index]) / batch_size)):
                    # copy over a consecutive batch to a list of batches
                    list_of_batches.append(
                        list_of_equal_length_data_lists[index][counter * batch_size: (counter+1) * batch_size]
                    )
    print("size of training data set:", len(list_of_batches), "batches of size", batch_size, ",",
          batch_size * len(list_of_batches), "samples total")
    # "free" list
    list_of_equal_length_data_lists = []
    gc.collect()

    return list_of_batches, data_validate


def init_loss_histories(data_validate):
    """
    prepares structure to hold individual loss histories
    :param data_validate: validation set
    :return: individual loss history structure, 0, and mse of corrected hpwl
    """
    # prepare individual loss histories, list contains records
    # of [loss_history, number_of_samples_for_this_feature_length]
    individual_loss_histories_validate = []
    for data in data_validate:
        while len(individual_loss_histories_validate) < (len(data.coordinate_pairs) - 1):
            individual_loss_histories_validate.append([[], 0, 0])
        individual_loss_histories_validate[len(data.coordinate_pairs) - 2][1] += 1
    final_individual_loss_histories = 0

    # compute loss of original bounding box cost for comparison
    loss_corrected_hpwl = 0
    for data in data_validate:
        if loss_function == 'mean_squared_error':
            squared_error = (data.corrected_hpwl - data.true_cost) * (data.corrected_hpwl - data.true_cost)
            loss_corrected_hpwl += squared_error
            individual_loss_histories_validate[len(data.coordinate_pairs) - 2][2] += squared_error
        else:
            print("ERROR: loss function not implemented")
            sys.exit("failed to compute loss function: not implemented.")

    # finalize mean loss value of original BB cost
    loss_corrected_hpwl /= len(data_validate)

    # finalize individual mean loss values of original BB cost
    for individual_loss_list_index in range(len(individual_loss_histories_validate)):
        if not individual_loss_histories_validate[individual_loss_list_index][1] == 0:
            individual_loss_histories_validate[individual_loss_list_index][2] /= \
                individual_loss_histories_validate[individual_loss_list_index][1]

    return individual_loss_histories_validate, final_individual_loss_histories, loss_corrected_hpwl


def define_model(lstm_layer_count: int, dense_layer_count: int, inflation_type,
                 validation_model: bool) -> tf.keras.Model:
    """
    define and compile a keras model based on the given parameters
    :param lstm_layer_count: number of lstm layers, including input layer
    :param dense_layer_count: number of dense layers, including output layer
    :param inflation_type: the distribution of neurons over the model: one of
        'inflating': starting with 4 neurons in input layer, every subsequent layer has 4 additional neurons
        'deflating': every subsequent layer has 4 neurons less than the preceding layer, ending with 4 neurons in the
                     layer immediately before the final dense layer
        'bloating':  starting with 4 neurons in input layer, every subsequent lstm layer has 4 additional neurons,
                     every subsequent dense layer has 4 neurons less than the preceding layer
        the final dense layer always has 1 neuron.
    :param validation_model: Flag whether to produce the validation model or the training model
    (differing in input shape)
    :return: the compiled model
    """
    # model definition
    model = tf.keras.models.Sequential()

    return_sequences = lstm_layer_count > 1
    neuron_count = (4*(lstm_layer_count+dense_layer_count-1)) if inflation_type == "deflating" else 4
    # add first / input layer
    model.add(
        tf.keras.layers.LSTM(
            neuron_count,
            batch_input_shape=(batch_size if not validation_model else 1, None, 2),
            return_sequences=return_sequences
        )
    )

    # add intermediary lstm layers
    for _ in range(1, lstm_layer_count - 1):
        neuron_count = max(neuron_count - 4, 1) if inflation_type == "deflating" else neuron_count + 4
        model.add(tf.keras.layers.LSTM(neuron_count, return_sequences=True))

    if lstm_layer_count > 1:
        # add last lstm layer
        neuron_count = max(neuron_count - 4, 1) if inflation_type == "deflating" else neuron_count + 4
        model.add(tf.keras.layers.LSTM(neuron_count, return_sequences=False))

    # add intermediate dense layers
    neuron_count = (
        max(neuron_count - 4, 1)
        if
        inflation_type != "inflating"
        else
        neuron_count + 4
    )
    for _ in range(dense_layer_count - 1):
        model.add(tf.keras.layers.Dense(neuron_count))
        neuron_count = max(neuron_count - 4, 1) if inflation_type != "inflating" else neuron_count + 4

    # add final dense layer
    model.add(tf.keras.layers.Dense(1))

    model.compile(loss=loss_function, optimizer=optimizer_choice)
    model.summary()

    return model


def train_model(model: tf.keras.Model, model_for_validation: tf.keras.Model, list_of_batches: list, data_validate,
                current_basepath: str):
    """
    trains the model using a custom training loop and early stopping
    :param model: the model to train
    :param model_for_validation: an identical model except for the input shape for manual validation
    :param list_of_batches: training set, as list of equal-length batches, each containing only samples of equal
    terminal count
    :param data_validate: validation set
    :param current_basepath: path to directory to save plots, logs, and teh trained model in
    :return: nothing, modifies filesystem
    """
    # create plot save folder
    plot_basepath = os.path.abspath(os.path.join(current_basepath, "plots/"))
    os.makedirs(plot_basepath)
    # history of training loss
    loss_history_train = []
    # history of validation loss
    loss_history_validate = []
    # history of "reference training loss"
    loss_history_train_reference = []
    # init individual loss histories
    individual_loss_histories_validate, final_individual_loss_histories, \
        loss_corrected_hpwl = init_loss_histories(data_validate)
    # init early stopping variables
    early_stopping_counter = 0
    best_val_loss = math.inf
    early_stopping_checkpoint = None
    # model epochs
    for epoch_count in range(epochs):
        gc.collect()
        print("epoch #", epoch_count)
        # shuffle the individual batches (externally)
        np.random.shuffle(list_of_batches)
        #
        loss_history_train.append(0)
        # in each epoch train on all the training data, one batch at a time
        for batch_counter in range(len(list_of_batches)):
            print("epoch(" + str(epoch_count) + "/" + str(epochs - 1) + ") batch #", batch_counter)
            # shuffle the specific batch (internally)
            np.random.shuffle(list_of_batches[batch_counter])
            # prepare the data as input to the model
            x_train = np.asarray([data.coordinate_pairs for data in list_of_batches[batch_counter]])
            x_train = x_train.reshape(batch_size, len(list_of_batches[batch_counter][0].coordinate_pairs), 2)
            y_train = np.asarray([data.true_cost for data in list_of_batches[batch_counter]])
            # train on one batch
            loss_history_train_tmp = model.fit(x_train, y_train, epochs=1)
            # mean squared error can be summed up and later devided by the number of batches, as long as each batch
            # is of equal size
            loss_history_train[epoch_count] += loss_history_train_tmp.history['loss'][0]
        # finalize mean squared error of train run
        loss_history_train[epoch_count] /= len(list_of_batches)
        # copy weights to the validation model with batch size of 1
        model_for_validation.set_weights(model.get_weights())
        # validate
        produced_results = []
        # reset to 0 (might have been used above)
        squared_loss_sum = 0
        # prepare individual loss records
        for individual_loss_list_index in range(len(individual_loss_histories_validate)):
            if not individual_loss_histories_validate[individual_loss_list_index][1] == 0:
                individual_loss_histories_validate[individual_loss_list_index][0].append(0)
        # use the whole validation set
        for data in data_validate:
            result = model_for_validation.predict(
                np.asarray(data.coordinate_pairs).reshape(1, len(data.coordinate_pairs), 2)
            )
            # log produced results for plotting (only for first, middle and last iteration because of visual clutter)
            if (
                    (epoch_count == 0)
                    or
                    (epoch_count == epochs - 1)
                    or
                    (epoch_count == int(epochs / 2))
                    or
                    (early_stopping_counter > early_stopping_patience)
            ):
                produced_results.append(result)
            # compute validation loss
            if loss_function == 'mean_squared_error':
                squared_error = (result - data.true_cost) * (result - data.true_cost)
                if print_high_error_samples and squared_error > 5:
                    print("large error detected:", squared_error)
                    print("expected value:", data.true_cost)
                    print("computed value:", result)
                    print("sequence length:", len(data.coordinate_pairs))
                    print("sequence:", data.coordinate_pairs)
                squared_loss_sum += squared_error
                individual_loss_histories_validate[len(data.coordinate_pairs) - 2][0][epoch_count] += squared_error
            else:
                print("ERROR: loss function not implemented")
                sys.exit("failed to compute loss function: not implemented.")
        # finalize loss computation
        current_val_loss = float(squared_loss_sum / len(data_validate))
        # perform early stopping routine
        if current_val_loss < best_val_loss:
            print("loss improved from {} to {}".format(best_val_loss, current_val_loss))
            # model improved, reset early stopping counter
            early_stopping_counter = 0
            # save current model weights as checkpoint
            early_stopping_checkpoint = model.get_weights()
            # update bsf val loss
            best_val_loss = current_val_loss
        else:
            print("loss did not improved from {} (currently {})".format(best_val_loss, current_val_loss))
            print("\tpatience left: {}".format(early_stopping_patience - early_stopping_counter))
            # model did not improve, increase counter
            early_stopping_counter += 1
        # log the mean loss for this epoch
        loss_history_validate.append(current_val_loss)
        # finalize individual mean loss values for this epoch
        for individual_loss_list_index in range(len(individual_loss_histories_validate)):
            if not individual_loss_histories_validate[individual_loss_list_index][1] == 0:
                individual_loss_histories_validate[individual_loss_list_index][0][epoch_count] /= \
                    individual_loss_histories_validate[individual_loss_list_index][1]
        # optionally compute reference train error (= error produced on training set with same Network state used for
        # calculating validation error
        squared_loss_sum = 0
        if (
                compute_and_plot_reference_train_error
                or
                (epoch_count == epochs - 1)
                or
                (early_stopping_counter > early_stopping_patience)
        ):
            for batch in list_of_batches:
                for data in batch:
                    result = model_for_validation.predict(
                        np.asarray(data.coordinate_pairs).reshape(1, len(data.coordinate_pairs), 2))
                    # compute validation loss
                    if loss_function == 'mean_squared_error':
                        squared_error = (result - data.true_cost) * (result - data.true_cost)
                        squared_loss_sum += squared_error
                    else:
                        print("ERROR: loss function not implemented")
                        sys.exit("failed to compute loss function: not implemented.")
            # log the mean loss for this epoch
            loss_history_train_reference.append(float(squared_loss_sum / (len(list_of_batches) * batch_size)))

        # plot expected and produced results (only for first, middle and last iteration because of visual clutter)
        if (
                (epoch_count == 0)
                or
                (epoch_count == epochs - 1)
                or
                (epoch_count == int(epochs / 2))
                or
                (early_stopping_counter > early_stopping_patience)
        ):
            plt.title("predictions against true values, epoch " + str(epoch_count))
            plt.scatter(range(validation_plotting_point_count)
                        if validation_plotting_point_count < len(produced_results)
                        else range(len(produced_results)),
                        produced_results[:validation_plotting_point_count]
                        if validation_plotting_point_count < len(produced_results)
                        else produced_results,
                        c='r', label='predicted_cost')
            plt.scatter(range(validation_plotting_point_count)
                        if validation_plotting_point_count < len(data_validate)
                        else range(len(data_validate)),
                        [data.true_cost for data in data_validate][:validation_plotting_point_count]
                        if validation_plotting_point_count < len(data_validate)
                        else [data.true_cost for data in data_validate],
                        c='g', label='true_cost')
            plt.scatter(range(validation_plotting_point_count)
                        if validation_plotting_point_count < len(data_validate)
                        else range(len(data_validate)),
                        [data.corrected_hpwl for data in data_validate][:validation_plotting_point_count]
                        if validation_plotting_point_count < len(data_validate)
                        else [data.corrected_hpwl for data in data_validate],
                        c='b', label='corrected_hpwl')
            plt.legend(loc='best')
            plt.savefig(plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "scatterplot_" +
                        ("initial" if (epoch_count == 0) else ("final" if (epoch_count == epochs - 1) else "midway")) +
                        ".png", bbox_inches='tight')
            plt.show()

        # plot combined validation loss over epochs
        plt.title("loss plot for whole validation data set")
        plt.xlabel("epoch")
        plt.ylabel(loss_function)
        plt.yscale('log')
        plt.plot(range(epoch_count + 1), loss_history_validate, 'bo-', label='validation loss')
        plt.plot(range(epoch_count + 1), loss_history_train, 'gx-', label='training loss')
        if (
                compute_and_plot_reference_train_error
                or
                (epoch_count == epochs - 1)
                or
                (early_stopping_counter > early_stopping_patience)
        ):
            if not compute_and_plot_reference_train_error:
                reference_loss_last_iter = loss_history_train_reference[0]
                loss_history_train_reference = []
                for epoch_count_tmp in range(epoch_count):
                    loss_history_train_reference.append(0)
                loss_history_train_reference.append(reference_loss_last_iter)
            plt.plot(range(epoch_count + 1), loss_history_train_reference, 'r*-', label='reference training loss')
        plt.axhline(y=loss_corrected_hpwl, color='y', linestyle='-', label='corrected_hpwl loss')
        plt.legend(loc='best')
        if epoch_count == epochs - 1 or (early_stopping_counter > early_stopping_patience):
            plt.savefig(
                plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "loss.png",
                bbox_inches='tight'
            )
        plt.show()

        # plot individual loss histories in one combined plot for easy qualitative comparison at the end
        # if epoch_count == epochs - 1:
        if (
                print_and_plot_stats_every_epoch
                or
                (epoch_count == epochs - 1)
                or
                (early_stopping_counter > early_stopping_patience)
        ):
            # extract only non-empty histories and assign subplot names
            column_names = []
            filtered_individual_loss_histories = []
            filtered_individual_original_loss_histories = []
            for individual_loss_list_index in range(len(individual_loss_histories_validate)):
                if not individual_loss_histories_validate[individual_loss_list_index][1] == 0:
                    column_names.append(str(individual_loss_list_index + 2))
                    filtered_individual_loss_histories.append(
                        individual_loss_histories_validate[individual_loss_list_index][0]
                    )
                    individual_original_loss_tmp = []
                    for count in range(len(individual_loss_histories_validate[individual_loss_list_index][0])):
                        individual_original_loss_tmp.append(
                            individual_loss_histories_validate[individual_loss_list_index][2]
                        )
                    filtered_individual_original_loss_histories.append(individual_original_loss_tmp)

            # prepare and print the combined plot
            # prepare data
            df_individual_loss_histories = pd.DataFrame(
                np.asarray(filtered_individual_loss_histories).reshape(
                    len(filtered_individual_loss_histories),
                    epoch_count + 1
                ).T,
                columns=np.asarray(column_names)
            )
            df_individual_original_loss_histories = pd.DataFrame(
                np.asarray(filtered_individual_original_loss_histories).reshape(
                    len(filtered_individual_original_loss_histories),
                    epoch_count + 1
                ).T,
                columns=np.asarray(column_names)
            )

            print("corrected_hpwl loss history:")
            print(df_individual_original_loss_histories)
            # create plot
            fig1, ax1 = plt.subplots(figsize=(20, 15))
            # assign different colors to different histories
            colors = sns.cubehelix_palette(len(filtered_individual_loss_histories), rot=0.9)
            df_individual_loss_histories.plot(color=colors, ax=ax1, linestyle='-')
            df_individual_original_loss_histories.plot(color=colors, ax=ax1, linestyle='--')
            # generate the legend
            plt.semilogy()
            plt.legend(ncol=4, loc='best')
            # specify title and axis labels
            plt.title("individual loss histories for validation sequences with different lengths")
            plt.xlabel("epoch")
            plt.ylabel(loss_function)
            # if it is the final plot save it (also save a plot just for the initial phase)
            if (
                    epoch_count == epochs - 1
                    or
                    epoch_count == int(epochs / 3)
                    or
                    (early_stopping_counter > early_stopping_patience)
            ):
                final_individual_loss_histories = df_individual_loss_histories
                plt.savefig(
                    plot_basepath + (
                        "limited_data_" if data_limit_flag else "full_data_"
                    ) + "loss_individual_" + (
                        "final"
                        if
                        (epoch_count == epochs - 1) or (early_stopping_counter > early_stopping_patience)
                        else
                        "initial"
                    ) + ".png",
                    bbox_inches='tight'
                )
            # finally make the plot visible
            plt.show()

            print("validation loss history:")
            print(df_individual_loss_histories)
            if(
                (epoch_count == epochs - 1)
                or
                (early_stopping_counter > early_stopping_patience)
            ):
                df_individual_loss_histories.to_csv(
                    os.path.abspath(os.path.join(current_basepath, "individual_loss_histories.csv"))
                )
            print("loss history:")
            print(loss_history_validate)
        # check if training finished due to early stopping
        if early_stopping_counter > early_stopping_patience:
            # patience exhausted, abort training (best model will be saved from checkpointed weights saved)
            break

    gc.collect()

    model_for_validation.set_weights(early_stopping_checkpoint)
    model_for_validation.save(os.path.abspath(os.path.join(current_basepath, "model")), include_optimizer=False)

    with open(
            plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "hyperparameters.txt", "w"
    ) as text_file:
        print("batch size: {}".format(batch_size), file=text_file)
        print("number of epochs: {}".format(epochs), file=text_file)
        print("loss function: {}".format(loss_function), file=text_file)
        print("optimizer: {}".format(optimizer_choice), file=text_file)
        print("numpy random number generator seed: {}".format(np_random_seed), file=text_file)
        print("data limit factor: {}".format("none" if not data_limit_flag else data_limit), file=text_file)
    with open(
            plot_basepath + ("limited_data_" if data_limit_flag else "full_data_") + "loss_history.txt", "w"
    ) as text_file:
        print("combined validation loss history:", file=text_file)
        print("", file=text_file)
        print(loss_history_validate, file=text_file)
        print("", file=text_file)
        print("individual validation loss histories:", file=text_file)
        print("", file=text_file)
        print(final_individual_loss_histories, file=text_file)


def train_one_model_variant(lstm_layer_count, dense_layer_count, inflation_type, list_of_batches,
                            data_validate):
    """
    creates a model based on teh given parameters and trains it, saving it to disk
    :param lstm_layer_count: number of lstm layers
    :param dense_layer_count: number of dense layers
    :param inflation_type: the distribution of neurons over the model: one of
        'inflating': starting with 4 neurons in input layer, every subsequent layer has 4 additional neurons
        'deflating': every subsequent layer has 4 neurons less than the preceding layer, ending with 4 neurons in the
                     layer immediately before the final dense layer
        'bloating':  starting with 4 neurons in input layer, every subsequent lstm layer has 4 additional neurons,
                     every subsequent dense layer has 4 neurons less than the preceding layer
        the final dense layer always has 1 neuron.
    :param list_of_batches: training set, as list of equal-length batches, each containing only samples of equal
    terminal count
    :param data_validate: validation set
    :return: nothing, modifies filesystem
    """
    print("\n\n\ntraining model '{}_lstm_layers_{}_dense_layers_{}'\n\n\n".format(
            lstm_layer_count, dense_layer_count, inflation_type
    ))

    current_model = define_model(lstm_layer_count, dense_layer_count, inflation_type, False)
    current_model_for_validation = define_model(lstm_layer_count, dense_layer_count, inflation_type, True)

    current_basepath = os.path.abspath(
        "./models/rnn/{}_lstm_layers_{}_dense_layers_{}".format(
            lstm_layer_count, dense_layer_count, inflation_type
        )
    )
    train_model(current_model, current_model_for_validation, list_of_batches,
                data_validate, current_basepath)


lstm_layer_counts = [3, 2, 1]
dense_layer_counts = [2, 1]
inflation_types = ["inflating", "deflating", "bloating"]

if __name__ == "__main__":

    # load train data characteristics
    batches, data_val = load_data()

    # HPO loop (grid search over few points because of long runtime)
    for current_lstm_layer_count in lstm_layer_counts:
        for current_dense_layer_count in dense_layer_counts:
            for current_inflation_type in inflation_types:
                train_one_model_variant(current_lstm_layer_count, current_dense_layer_count, current_inflation_type,
                                        batches, data_val)
