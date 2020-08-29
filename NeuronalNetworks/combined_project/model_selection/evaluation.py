from model_selection.util import *

best_rnn = "asdf"
best_cnn = "asdf"

evaluation_basepath = os.path.abspath("./evaluation_results")
evaluation_reference_path = os.path.abspath("./evaluation_results/reference/")
evaluation_rnn_path = os.path.abspath("./evaluation_results/rnn/")
evaluation_cnn_path = os.path.abspath("./evaluation_results/cnn/")


def eval_type(circuit_path, circuit_name, target_path, type: str, inner_num, reference_inner_num: int):

    avg_time = 0
    qualities = []

    set_vpr_context(type)

    for i in range(redundancy_count):
        current_specific_path = os.path.abspath(
            os.path.join(
                os.path.join(
                    target_path,
                    "reference_inner_num_{}".format(reference_inner_num)
                ),
                "placement_nr_{}".format(i)
            )
        )
        time, quality = time_placement(
            circuit_path, circuit_name, current_specific_path, place_only=False, inner_num=inner_num
        )
        copy_placement_and_routing(circuit_path, circuit_name, current_specific_path)
        avg_time += time
        qualities.append(quality)

    reset_vpr_context()

    avg_time = avg_time / redundancy_count

    return avg_time, qualities


if __name__ == "__main__":
    with open("runtime_quality_map.pkl", "rb") as f:
        runtime_quality_map = pickle.load(f)
    # ensure tf lib is available
    execute("set PATH=%PATH%;$PWD/src/ml_integration/lib/")

    try:
        with open("./eval_performance_map.pkl", "rb") as f:
            performance_map = pickle.load(f)
    except FileNotFoundError:
        performance_map = dict()

    rnn_inner_num_factor = (
        (
            # time used by reference at eval_reference_inner_num
            runtime_quality_map[("reference", eval_circuits[0])][1]
            /
            eval_reference_inner_num
        )  # = time of reference at inner_num = 1
        /
        (
            runtime_quality_map[(best_rnn, eval_circuits[0])][0]  # actual time used by best_rnn at initial_inner_num
            /
            initial_inner_num
        )  # = time of best_rnn at inner_num = 1
    )

    cnn_inner_num_factor = (
        (
            # time used by reference at eval_reference_inner_num
            runtime_quality_map[("reference", eval_circuits[0])][1]
            /
            eval_reference_inner_num
        )  # = time of reference at inner_num = 1
        /
        (
            runtime_quality_map[(best_cnn, eval_circuits[0])][0]  # actual time used by best_rnn at initial_inner_num
            /
            initial_inner_num
        )  # = time of best_rnn at inner_num = 1
    )

    # evaluate each circuit
    for circuit in test_circuits:
        # get absolute circuit path
        current_circuit_path = os.path.abspath(os.path.join(
            benchmark_basepath,
            circuit
        ))
        # pack the circuit
        pack_circuit(current_circuit_path, circuit, model_base_path)
        # evaluate on all sampling points
        for inner_num_reference in test_sampling_points:
            # eval reference
            # (if not already done, supports breaking and restarting the process due to potentially large runtime)
            try:
                performance_map[("reference", circuit, inner_num_reference)]
            except KeyError:
                performance_map[("reference", circuit, inner_num_reference)] = eval_type(
                    current_circuit_path, circuit, evaluation_reference_path, "reference",
                    inner_num_reference, inner_num_reference
                )
                # save progress
                with open("./eval_performance_map.pkl", "wb") as f:
                    pickle.dump(performance_map, f, pickle.HIGHEST_PROTOCOL)
            # eval rnn
            # (if not already done, supports breaking and restarting the process due to potentially large runtime)
            try:
                performance_map[("rnn", circuit, inner_num_reference)]
            except KeyError:
                performance_map[("rnn", circuit, inner_num_reference)] = eval_type(
                    current_circuit_path, circuit, evaluation_rnn_path, "rnn",
                    inner_num_reference * rnn_inner_num_factor, inner_num_reference
                )
                # save progress
                with open("./eval_performance_map.pkl", "wb") as f:
                    pickle.dump(performance_map, f, pickle.HIGHEST_PROTOCOL)
            # eval cnn
            # (if not already done, supports breaking and restarting the process due to potentially large runtime)
            try:
                performance_map[("cnn", circuit, inner_num_reference)]
            except KeyError:
                performance_map[("cnn", circuit, inner_num_reference)] = eval_type(
                    current_circuit_path, circuit, evaluation_cnn_path, "cnn",
                    inner_num_reference * cnn_inner_num_factor, inner_num_reference
                )
                # save progress
                with open("./eval_performance_map.pkl", "wb") as f:
                    pickle.dump(performance_map, f, pickle.HIGHEST_PROTOCOL)

    with open("./eval_performance_map.pkl", "wb") as f:
        pickle.dump(performance_map, f, pickle.HIGHEST_PROTOCOL)
