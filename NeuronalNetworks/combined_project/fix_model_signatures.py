#
# source: https://stackoverflow.com/a/63414614
#

from model_selection.util import *
import tensorflow as tf

rnn_model_base_path = os.path.abspath("./models/rnn")
cnn_model_base_path = os.path.abspath("./models/conv")


def rename(model, layer, new_name):
    """
    rename a layer of a saved_model
    :param model: the loaded keras model
    :param layer: old name of the layer
    :param new_name: new name of the layer
    :return: nothing, modifies model
    """
    def _get_node_suffix(name):
        for old_name in old_nodes:
            if old_name.startswith(name):
                return old_name[len(name):]

    old_name = layer.name
    old_nodes = list(model._network_nodes)
    new_nodes = []

    for l in model.layers:
        if l.name == old_name:
            l._name = new_name
            # vars(l).__setitem__('_name', new)  # bypasses .__setattr__
            new_nodes.append(new_name + _get_node_suffix(old_name))
        else:
            new_nodes.append(l.name + _get_node_suffix(l.name))
    model._network_nodes = set(new_nodes)


def rename_models(models_base_path, new_name):
    """
    fix the signature definition of all models saved in the given location by renaming their input layer. this also
    changes the signature definition after loading and saving the model again.
    :param models_base_path: directory containing the models to be changed, each saved model located in file
    '[models_base_path]/[some_subfolder]/model/saved_model.pb'
    :param new_name: new name for the input signature / first layer
    :return: nothing, modifies filesystem
    """
    # get a list of all models saved in [models_base_path]
    models = os.listdir(models_base_path)
    models = [model for model in models if "." not in model]
    # process each model
    for model_name in models:
        # path to subfolder holding current saved_model.pb
        model_path = os.path.abspath(os.path.join(os.path.join(models_base_path, model_name), "model"))
        # load model
        model = tf.keras.models.load_model(model_path)
        # print model structure (includes input layer name)
        print(model.summary())
        # rename the input layer
        rename(model, model.layers[0], new_name)
        # print model structure again, input layer name should have changed to [new_name]
        model.summary()
        # Save the model. signature definition not yet updated...
        tf.keras.models.save_model(
            model,
            model_path,
            include_optimizer=False
        )
        # load the model again
        model = tf.keras.models.load_model(model_path)
        # Save the model again, signature_def is only updated the second time...
        tf.keras.models.save_model(
            model,
            model_path,
            include_optimizer=False
        )
        # finished with this model


if __name__ == "__main__":
    # fix all RNNs
    rename_models(rnn_model_base_path, "lstm_renamed")
    # fix all CNNs
    rename_models(cnn_model_base_path, "flatten_8")
