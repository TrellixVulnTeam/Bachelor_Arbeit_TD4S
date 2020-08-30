import os
import pickle
import shutil
import numpy as np

redundancy_count = 3

eval_circuits = ["raygentop", "mkDelayWorker32B"]
initial_inner_num = 0.005
eval_reference_inner_num = 10

test_circuits = ["", "", ""]
test_sampling_points = [1, 10, 50]

model_base_path = os.path.abspath("../models/")

rnn_model_base_path = os.path.abspath(os.path.join(model_base_path, "rnn"))
cnn_model_base_path = os.path.abspath(os.path.join(model_base_path, "conv"))

vpr_base_path = os.path.abspath("../../../VPR_PROJECT/vpr/")
rnn_model_target_path = os.path.abspath(os.path.join(vpr_base_path, "src/ml_integration/model_lstm/model"))
cnn_model_target_path = os.path.abspath(os.path.join(vpr_base_path, "src/ml_integration/model_cnn/model"))

vpr_path = os.path.abspath(os.path.join(vpr_base_path, "vpr"))
arch_path = os.path.abspath(os.path.join(vpr_base_path, "../vtr_flow/arch/timing/k6_frac_N10_mem32K_40nm.xml"))
benchmark_basepath = os.path.abspath(os.path.join(vpr_base_path, "../vtr_flow/benchmarks/vtr_benchmarks_blif/"))

log_path = os.path.abspath("./vpr_stdout.log")


def execute(command: str):
    os.system(command)


def move_log_file(target_path, circuit_name):
    """
    backs up the vpr log file by copying it to the specified directory
    :param target_path: absolute path of directory to store the files
    :param circuit_name:
    :return:
    """
    try:
        os.makedirs(target_path)
    except FileExistsError:
        pass
    os.rename(log_path, os.path.abspath(os.path.join(target_path, "vpr_stdout_{}.log".format(circuit_name))))


def delete_log_file():
    try:
        os.remove(log_path)
    except FileNotFoundError:
        pass


def pack_circuit(circuit_path, circuit_name, target_path):
    """
    packs the circuit and copies the netlist to the specified path as backup
    :param circuit_path: absolute path to circuit file without .blif file extension
    :param circuit_name:
    :param target_path: absolute path of directory to store the file
    :return:
    """
    set_vpr_context("reference")
    execute("{} {} {}.blif --pack".format(vpr_path, arch_path, circuit_path))
    try:
        os.makedirs(target_path)
    except FileExistsError:
        pass
    shutil.copyfile(
        "{}.net".format(circuit_path),
        os.path.abspath(os.path.join(target_path, "{}.net".format(circuit_name)))
    )
    delete_log_file()
    reset_vpr_context()


def time_placement(circuit_path, circuit_name, target_path, place_only, inner_num=eval_reference_inner_num):
    """
    places and optionally routes the already packed circuit. bycks up the log file and returns speed and quality
    :param circuit_path: absolute path to circuit file without .blif file extension
    :param circuit_name:
    :param target_path: absolute path of directory to store the file
    :param place_only: flag to only place or also route
    :param inner_num: value for "--inner_num" parameter to pass to vpr, factor for moves per temperature step
    :return: time needed to place the circuit if place_only, else also placement quality
    """
    if place_only and os.path.isfile(
            os.path.abspath(
                os.path.join(
                    os.path.join(
                        target_path,
                        "placement_nr_2"
                    ),
                    "vpr_stdout_{}.log".format(circuit_name)
                )
            )
    ):
        with open(os.path.abspath(
                os.path.join(os.path.join(target_path, "placement_nr_2"), "vpr_stdout_{}.log".format(circuit_name))
        ), "r") as f:
            lines = f.readlines()
        for line in lines:
            if "--place --route --inner_num" in line:
                return None, float(line.split(" ")[6])
    elif os.path.isfile(os.path.abspath(os.path.join(target_path, "vpr_stdout_{}.log".format(circuit_name)))):
        with open(os.path.abspath(os.path.join(target_path, "vpr_stdout_{}.log".format(circuit_name))), "r") as f:
            lines = f.readlines()
        target_path = None
    else:
        random_seed = np.random.randint(2147483647)
        execute("{} {} {}.blif --place{}--inner_num {} --seed {}".format(
            vpr_path, arch_path, circuit_path, " " if place_only else " --route ", inner_num, random_seed)
        )

        with open(os.path.abspath("./vpr_stdout.log"), "r") as f:
            lines = f.readlines()
    placement_time = -1
    routing_width = -1
    routing_critical_path = -1
    for line in lines:
        if line.startswith("# Placement took "):
            placement_time = float(line.split(" ")[3])
        if line.startswith("Circuit successfully routed with a channel width factor of"):
            routing_width = int(line.split(" ")[9].split(".")[0])
        if line.startswith("Final critical path:"):
            routing_critical_path = float(line.split(" ")[3])
    if not place_only and target_path is not None:
        move_log_file(target_path, circuit_name)
    else:
        delete_log_file()
    if place_only:
        return placement_time, None
    else:
        return placement_time, (routing_width, routing_critical_path)


def set_vpr_context(context: str):
    """
    activates a certain mode of vpr by copying the specific executable to the expected location
    :param context: the mode to activate, one of "reference", "rnn", "cnn", "cnn_no_conv"
    :return: nothing, modifies file system
    """
    try:
        os.remove("{}.exe".format(vpr_path))
    except FileNotFoundError:
        pass
    shutil.copyfile("{}_{}.exe".format(vpr_path, context), "{}.exe".format(vpr_path))


def reset_vpr_context():
    """
    resets vpr to no mode at all by removing the "vpr.exe" executable
    :return: nothing, modifies file system
    """
    os.remove("{}.exe".format(vpr_path))


def deploy_model(type: str, model_path):
    """
    deploys a specific NN to vpr by copying the specific "model" folder to its appropriate place in vpr
    :param type: the type of NN to deploy, one of "rnn", "cnn" ("cnn_no_conv" is handled by passing "cnn")
    :param model_path: the absolute path to the specific NN (location of the "model" folder)
    :return: nothing, modifies file system
    """
    remove_model(type)
    shutil.copytree(
        model_path,
        rnn_model_target_path if type == "rnn" else cnn_model_target_path
    )


def remove_model(type: str):
    """
    "un-deploys" a specific NN to vpr by deleting the specific "model" folder from its respective place in vpr
    :param type: the type of NN to remove, one of "rnn", "cnn" ("cnn_no_conv" is handled by passing "cnn")
    :return: nothing, modifies file system
    """
    shutil.rmtree(rnn_model_target_path if type == "rnn" else cnn_model_target_path, ignore_errors=True)


def copy_placement_and_routing(circuit_path, circuit_name: str, target_path: str):
    """
    saves the produced placement and routing files by copying them to the specified directory
    :param circuit_path: absolute path to circuit file without .blif file extension
    :param circuit_name:
    :param target_path: absolute path of directory to store the files
    :return: nothing, modifies file system
    """
    if os.path.isfile(os.path.abspath(os.path.join(target_path, "{}.place".format(circuit_name)))):
        return
    try:
        os.makedirs(target_path)
    except FileExistsError:
        pass
    os.rename(
        "{}.place".format(circuit_path),
        os.path.abspath(os.path.join(target_path, "{}.place".format(circuit_name)))
    )
    os.rename(
        "{}.route".format(circuit_path),
        os.path.abspath(os.path.join(target_path, "{}.route".format(circuit_name)))
    )
