#
# source: https://stackoverflow.com/a/63414614
#

from model_selection.util import *
import tensorflow as tf

rnn_model_base_path = os.path.abspath("./models/rnn")
cnn_model_base_path = os.path.abspath("./models/conv")


def rename(model, layer, new_name):
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

    models = os.listdir(models_base_path)
    models = [model for model in models if "." not in model]

    for model_name in models:

        model_path = os.path.abspath(os.path.join(os.path.join(models_base_path, model_name), "model"))

        model = tf.keras.models.load_model(model_path)

        print(model.summary())

        rename(model, model.layers[0], new_name)
        model.summary()

        # Save the model.
        tf.keras.models.save_model(
            model,
            model_path,
            include_optimizer=False
        )

        model = tf.keras.models.load_model(model_path)

        # Save the model again, signature_def is only updated the second time...
        tf.keras.models.save_model(
            model,
            model_path,
            include_optimizer=False
        )


if __name__ == "__main__":
    rename_models(rnn_model_base_path, "lstm_renamed")
    rename_models(cnn_model_base_path, "flatten_8")
