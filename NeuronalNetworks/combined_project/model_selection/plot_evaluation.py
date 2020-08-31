import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits import mplot3d
import plotly.graph_objects as go
import os
import pickle
import pandas as pd

from model_selection.util import *

with open("eval_performance_map.pkl", "rb") as f:
    performance_map = pickle.load(f)


def print_result_table():
    keys = list(performance_map.keys())
    keys = [entry for entry in keys if isinstance(entry, tuple)]
    keys = [entry for entry in keys if entry[1] in test_circuits]
    tuples = [(entry[1], entry[2], entry[0]) for entry in keys]
    row_tuples = [("channel_width", "1"),
                ("channel_width", "2"),
                ("channel_width", "3"),
                ("channel_width", "avg"),
                ("critical_path", "1"),
                ("critical_path", "2"),
                ("critical_path", "3"),
                ("critical_path", "avg")]
    values = [
                {
                    ("channel_width", "1"): round(performance_map[key][1][0][0], 2),
                    ("channel_width", "2"): round(performance_map[key][1][1][0], 2),
                    ("channel_width", "3"): round(performance_map[key][1][2][0], 2),
                    ("channel_width", "avg"): round(np.asarray(performance_map[key][1])[:, 0].mean(), 2),
                    ("critical_path", "1"): round(performance_map[key][1][0][1], 2),
                    ("critical_path", "2"): round(performance_map[key][1][1][1], 2),
                    ("critical_path", "3"): round(performance_map[key][1][2][1], 2),
                    ("critical_path", "avg"): round(np.asarray(performance_map[key][1])[:, 1].mean(), 2)
                }
                for key
                in keys
            ]
    dict_eval = dict(
        zip(
            tuples,
            values
        )
    )
    index=pd.MultiIndex.from_tuples(tuples, names=['circuit', 'sampling_point', 'type'])
    index_rows=pd.MultiIndex.from_tuples(row_tuples, names=['metric', 'attempt'])
    df = pd.DataFrame(dict_eval, columns=index, index=index_rows).transpose()
    print(df)
    df.to_latex("evaluation_performance_table_latex.txt")


def get_perf(circuit, metric, type):

    values_ref = [
        (
            np.asarray(
                performance_map["reference", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].mean()
            if type == "mean" else
            np.asarray(
                performance_map["reference", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].min()
        )
        for sampling_point
        in test_sampling_points
    ]
    values_cnn = [
        (
            np.asarray(
                performance_map["cnn", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].mean()
            if type == "mean" else
            np.asarray(
                performance_map["cnn", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].min()
        )
        for sampling_point
        in test_sampling_points
    ]
    values_rnn = [
        (
            np.asarray(
                performance_map["rnn", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].mean()
            if type == "mean" else
            np.asarray(
                performance_map["rnn", circuit, sampling_point][1]
            )[:, 0 if metric == "channel_width" else 1].min()
        )
        for sampling_point
        in test_sampling_points
    ]

    return np.asarray(values_ref), np.asarray(values_cnn), np.asarray(values_rnn)


def plot_perf_over_sampling_points(values_ref, values_cnn, values_rnn, circuit, metric, type):
    plt.plot(values_ref, 'r', label="reference")
    plt.plot(values_cnn, 'b', label="cnn")
    plt.plot(values_rnn, 'g', label="rnn")
    plt.xticks(list(range(len(test_sampling_points))), test_sampling_points)
    plt.xlabel("sampling points")
    plt.ylabel("{} achieved {}".format(type, metric))
    plt.title("{} performance over sampling points (runtime aligned)\ncircuit '{}', metric '{}'".format(type, circuit, metric))
    plt.legend()
    plt.savefig("../../../Thesis/plots/eval-{}-{}-{}.png".format(circuit, "chan-width" if metric == metrics[0] else "critical-path", type))
    plt.show()


def plot_perf_over_sampling_points_one_circuit(circuit, metric, type):
    plot_perf_over_sampling_points(*get_perf(circuit, metric, type), circuit, metric, type)


def plot_perf_over_sampling_points_all_circuits(metric, type):
    values_ref = np.zeros(len(test_sampling_points))
    values_cnn = np.zeros(len(test_sampling_points))
    values_rnn = np.zeros(len(test_sampling_points))
    for circuit in test_circuits:
        values_ref_tmp, values_cnn_tmp, values_rnn_tmp = get_perf(circuit, metric, type)
        values_ref += values_ref_tmp
        values_cnn += values_cnn_tmp
        values_rnn += values_rnn_tmp
    values_ref = values_ref / len(test_circuits)
    values_cnn = values_cnn / len(test_circuits)
    values_rnn = values_rnn / len(test_circuits)
    plot_perf_over_sampling_points(values_ref, values_cnn, values_rnn, "combined", metric, type)


if __name__ == "__main__":
    # print_result_table()
    for current_type in ["mean", "min"]:
        for current_metric in metrics:
            for current_circuit in test_circuits:
                plot_perf_over_sampling_points_one_circuit(current_circuit, current_metric, current_type)
            plot_perf_over_sampling_points_all_circuits(current_metric, current_type)
