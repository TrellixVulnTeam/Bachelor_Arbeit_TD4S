import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from mpl_toolkits import mplot3d
import plotly.graph_objects as go
import os
import pickle
import pandas as pd

from model_selection.util import *


def plot_individual_loss_histories(values_low, values_mid, values_high):
    plt.plot(values_high, 'purple', label="mean over select high counts")
    plt.plot(values_mid, 'brown', label="mean over select medium counts")
    plt.plot(values_low, 'g', label="mean over select low counts")
    plt.xlabel("epoch")
    plt.yscale("log")
    plt.ylabel("mean_squared_error")
    plt.title("validation loss plot for predictions on different terminal counts\ncomputed on whole validation data set\nmodel: 3_lstm_layers_2_dense_layers_inflating")
    plt.legend()
    plt.savefig("../../../Thesis/plots/rnn-training-history-individual-3_lstm_layers_2_dense_layers_inflating.png")
    plt.show()


if __name__ == "__main__":
    hist = pd.read_csv(os.path.abspath(os.path.join(model_base_path, "tmp/3_lstm_layers_2_dense_layers_inflating/individual_loss_histories.csv")))
    hist = hist.to_numpy(dtype=float)
    print(hist.shape)
    hist_mid = hist[:, 20:25].mean(axis=1)
    hist_high = hist[:, 34]  # .mean(axis=1)
    hist_low = hist[:, 4:7].mean(axis=1)
    plot_individual_loss_histories(hist_low, hist_mid, hist_high)
