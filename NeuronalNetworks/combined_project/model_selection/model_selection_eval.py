from model_selection.util import *

rnn_model_base_path = os.path.abspath(os.path.join(model_base_path, "rnn"))
cnn_model_base_path = os.path.abspath(os.path.join(model_base_path, "conv"))


def time_reference(circuit_path: str, circuit_name: str, target_path: str):
    set_vpr_context("reference")
    time, quality = time_placement(circuit_path, circuit_name, target_path=target_path, place_only=False)
    print("reference took {}s at inner_num 10".format(time))
    runtime_quality_map[("reference", circuit_name)] = (-1, time, quality)
    reset_vpr_context()


def analyze_nns(circuit_path: str, circuit_name: str, type: str):
    """
    analyze all NN versions of a certain type (compliled version of vpr)
    :param circuit_path:
    :param circuit_name:
    :param type: type of the NNs: one of "rnn", "cnn", "cnn_no_conv"
    :return: nothing, modifies global runtime_quality_map
    """
    print("analyzing {}s...".format(type))
    set_vpr_context(type)
    models = os.listdir(rnn_model_base_path if type == "rnn" else cnn_model_base_path)
    reference_time = runtime_quality_map[("reference", circuit_name)][1]
    for model in models:
        print("analyzing model {}...".format(model))
        current_basepath = os.path.abspath(
            os.path.join(rnn_model_base_path if type == "rnn" else cnn_model_base_path, model)
        )
        deploy_model(
            type,
            os.path.abspath(os.path.join(current_basepath, "model"))
        )
        time = time_placement(circuit_path, circuit_name, None, place_only=True, inner_num=initial_inner_num)
        print("{} took {}s at inner_num {}".format(model, time, initial_inner_num))
        target_inner_num = initial_inner_num / time * reference_time
        target_time = 0
        channel_widths = []
        critical_paths = []
        for i in range(redundancy_count):
            current_specific_path = os.path.abspath(os.path.join(current_basepath, "placement_nr_{}".format(i)))
            target_time_tmp, quality_tmp = time_placement(
                circuit_path,
                circuit_name,
                current_specific_path,
                place_only=False,
                inner_num=target_inner_num
            )
            target_time += target_time_tmp
            channel_widths.append(quality_tmp[0])
            critical_paths.append(quality_tmp[1])
            copy_placement_and_routing(circuit_path, circuit_name, current_specific_path)
        target_time = target_time / 3
        print("{} took {}s at inner_num {}, achieving ({}, {})".format(
            model, time, target_inner_num, np.asarray(channel_widths).mean(), np.asarray(critical_paths).mean()))
        runtime_quality_map[(model, circuit_name)] = (time, target_time, (channel_widths, critical_paths))
        remove_model(type)
    reset_vpr_context()


if __name__ == "__main__":
    try:
        with open("runtime_quality_map.pkl", "rb") as f:
            runtime_quality_map = pickle.load(f)
    except FileNotFoundError:
        runtime_quality_map = dict()
    # ensure tf lib is available
    execute("set PATH=%PATH%;$PWD/src/ml_integration/lib/")

    for circuit in eval_circuits:
        current_circuit_path = os.path.abspath(os.path.join(
            benchmark_basepath,
            circuit
        ))
        # pack the circuit
        pack_circuit(current_circuit_path, circuit, model_base_path)
        # time reference
        time_reference(current_circuit_path, circuit, model_base_path)
        # set rnn vpr
        analyze_nns(current_circuit_path, circuit, "rnn")
        analyze_nns(current_circuit_path, circuit, "cnn")

    with open("./runtime_quality_map.pkl", "wb") as f:
        pickle.dump(runtime_quality_map, f, pickle.HIGHEST_PROTOCOL)
