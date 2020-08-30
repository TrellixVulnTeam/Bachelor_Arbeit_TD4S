import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits import mplot3d
import plotly.graph_objects as go
import os
import pickle
import pandas as pd

from model_selection.util import *

with open("runtime_quality_map.pkl", "rb") as f:
    runtime_quality_map = pickle.load(f)


def get_score(model: str, fixed_value: tuple) -> int:
    circuit, score = fixed_value
    quality = runtime_quality_map[(model, circuit)]
    if score == "channel_width":
        return np.asarray(quality[2][0]).mean()
    else:  # critical path length
        return np.asarray(quality[2][1]).mean()


def plot_model_scores_over_circuit(type: str):

    models = os.listdir(rnn_model_base_path if type == "rnn" else cnn_model_base_path)

    labels = [eval_circuits[0],
                'combined',
                eval_circuits[1]]


def plot_model_scores_over_hyperparams(circuit, metric, reference):
    """
    over layer defs (X) and inflation type (+ filter size) (Y)
    :param type:
    :return:
    """

    # models_cnn = os.listdir(cnn_model_base_path)
    # models_rnn = os.listdir(rnn_model_base_path)
    #
    # # layer defs
    # special_layer_counts = [model_name.split("_")[0] for model_name in models]
    # dense_layer_counts = [model_name.split("_")[3] for model_name in models]

    # inflation types

    y_labels_cnn = ["0 conv2d layers",
                    "1 conv2d layer",
                    "2 conv2d layers"]

    x_labels_cnn = ["inflating, 3",
                "deflating, 3",
                "inflating, 7",
                "deflating, 7"]

    def f_cnn(x_in, y_in, fixed_value):
        tmp = get_score(
            "{}_conv_layers_{}_kernel_size_{}".format(
                int(y_in),
                ("inflating" if x_in % 2 == 0 else "deflating"),
                (-1 if y_in == 0 else (3 if (x_in // 2) % 2 == 0 else 7))
            ),
            fixed_value
        )
        return tmp if tmp > 0 else 0.1

    plot_scores_of_one_model_in_3d(
        "mean achieved {}\nCNN models on circuit '{}'".format(metric, circuit), x_labels_cnn, y_labels_cnn, 'layer dimensions, conv2d kernel size', 'layers',
        metric,
        f_cnn, (circuit, metric), get_score("reference", (circuit, metric)) if reference else None
    )

    y_labels_rnn = ["(1, 1)",
                    "(1, 2)",
                    "(2, 1)",
                    "(2, 2)",
                    "(3, 1)",
                    "(3, 2)"]

    x_labels_rnn = ["inflating",
                "deflating",
                "bloating"]

    def f_rnn(x_in, y_in, fixed_value):
        tmp = get_score(
            "{}_lstm_layers_{}_dense_layers_{}".format(
                int(y_in) // 2 + 1,
                int(y_in) % 2 + 1,
                ("inflating" if x_in == 0 else "deflating" if x_in == 1 else "bloating")
            ),
            fixed_value
        )
        return tmp if tmp > 0 else 0.1

    plot_scores_of_one_model_in_3d(
        "mean achieved {}\nRNN models on circuit '{}'".format(metric, circuit), x_labels_rnn, y_labels_rnn, 'layer dimensions', 'lstm layers, dense layers',
        metric,
        f_rnn, (circuit, metric), get_score("reference", (circuit, metric)) if reference else None
    )

    print("reference value for {}: {}".format(metric, get_score("reference", (circuit, metric))))


def plot_scores_of_one_model_in_3d(title,
        x_labels: list, y_labels: list, x_axis_label: str, y_axis_label: str, z_axis_label: str,
        mapping_func, fixed_value, reference_value):

    # def symlog_shift(arr, shift=0):
    #     # shift array-like to symlog array with shift
    #     logv = np.abs(arr) * (10. ** shift)
    #     logv[np.where(logv < 1.)] = 1.
    #     logv = np.sign(arr) * np.log10(logv)
    #     return logv
    #
    # def symlog_shift_ticks(tks1, tks2, tks3, shift=0):
    #     # generate the tick position and the corresponding tick labels in symlog scale with shift
    #     # tks1, tks2, tks3: tick values in log scale
    #
    #     # tick positions to show in graph
    #     tkps = [-v - shift for v in tks1] + tks2 + [v + shift for v in tks3]
    #     # tkck labels in str
    #     tkls = ['$-10^{%d}$' % (v) for v in tks1] + [''] + ['$10^{%d}$' % (v) for v in tks3]
    #     return tkps, tkls

    def color(val):
        return cm.coolwarm(val)
    SHIFT = 1

    x = np.linspace(0, len(x_labels)-1, len(x_labels))  # number of augmentation methods
    y = np.linspace(0, len(y_labels)-1, len(y_labels))

    X, Y = np.meshgrid(x, y)

    x_flat = X.flatten()
    y_flat = Y.flatten()

    Z = [mapping_func(x_flat[i], y_flat[i], fixed_value) for i in range(len(x_labels)*len(y_labels))]

    Z = np.reshape(Z, (len(y_labels), len(x_labels)))

    # Z = symlog_shift(Z,shift=SHIFT)
    # ztkps, ztkls = symlog_shift_ticks([2, 1, 0, -1], [0], [-1, 0, 1, 2], shift=SHIFT)

    Z_colors = np.array([[color(z) for z in row] for row in Z]).reshape(Z.shape + (-1,))

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    ax.set_xticks(range(len(x_labels)))
    ax.set_xticklabels(x_labels, horizontalalignment='right')

    ax.set_yticks(range(len(y_labels)))
    ax.set_yticklabels(y_labels, horizontalalignment='left')

    # ax.set_zticks(ztkps)
    # ax.set_zticklabels(ztkls)

    if reference_value is not None:
        Z_const = [reference_value for i in range(len(x_labels) * len(y_labels))]
        Z_const = np.reshape(Z_const, (len(y_labels), len(x_labels)))
        ax.plot_surface(X, Y, Z_const, label='reference score', rstride=1, cstride=1,
                    cmap='viridis', edgecolor='none')

    ax.plot_surface(X, Y, Z, rstride=1, label='achieved score', cstride=1,
                    cmap='viridis', edgecolor='none')
    # ax.set_title('evaluation on model \"{}\"'.format(model.__str__()))
    ax.set_title(title)
    ax.set_xlabel(x_axis_label, labelpad=16)
    ax.set_ylabel(y_axis_label, labelpad=2)
    ax.set_zlabel(z_axis_label)
    # ax.set_zlim((0, 5))
    # ax.set_zbound((0, 5))
    ax.tick_params(labelsize=6)
    ax.tick_params(axis='x', pad=-4)
    ax.tick_params(axis='y', rotation=350, pad=-4)

    ax.view_init(30, 330)
    plt.show()


def print_result_table(circuit):
    keys = list(runtime_quality_map.keys())
    keys = [entry for entry in keys if isinstance(entry, tuple)]
    keys = [entry for entry in keys if entry[1] == circuit]
    keys = [entry for entry in keys if "lstm" in entry[0]]
    tuples = [(entry[0].split("_")[0], entry[0].split("_")[3], entry[0].split("_")[6]) for entry in keys]
    dict_lstm = dict(
        zip(
            tuples,
            [
                {
                    "channel_width": np.asarray(runtime_quality_map[key][1]).mean(),
                    "critical_path_ns": np.asarray(runtime_quality_map[key][2]).mean()
                }
                for key
                in keys
            ]
        )
    )
    index=pd.MultiIndex.from_tuples(tuples, names=['lstm_layer_count', 'dense_layer_count', 'structure'])
    df = pd.DataFrame(dict_lstm, columns=index)
    df.to_latex("model_selection_lstm_performance_table_{}_latex.txt".format(circuit))

    keys = list(runtime_quality_map.keys())
    keys = [entry for entry in keys if isinstance(entry, tuple)]
    keys = [entry for entry in keys if entry[1] == circuit]
    keys = [entry for entry in keys if "conv" in entry[0]]
    tuples = [(entry[0].split("_")[0], entry[0].split("_")[3], entry[0].split("_")[6]) for entry in keys]
    dict_lstm = dict(
        zip(
            tuples,
            [
                {
                    "channel_width": np.asarray(runtime_quality_map[key][1]).mean(),
                    "critical_path_ns": np.asarray(runtime_quality_map[key][2]).mean()
                }
                for key
                in keys
            ]
        )
    )
    index=pd.MultiIndex.from_tuples(tuples, names=['conv_layer_count', 'structure', 'kernel_size'])
    df = pd.DataFrame(dict_lstm, columns=index)
    df.to_latex("model_selection_cnn_performance_table_{}_latex.txt".format(circuit))



if __name__ == "__main__":
    plot_model_scores_over_hyperparams(eval_circuits[0], "channel_width", reference=False)
    plot_model_scores_over_hyperparams(eval_circuits[0], "critical path length (ns)", reference=False)

    print_result_table(eval_circuits[0])
