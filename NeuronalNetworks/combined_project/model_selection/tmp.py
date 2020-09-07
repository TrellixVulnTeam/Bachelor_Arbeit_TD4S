from model_selection.util import *
from model_selection.evaluation import *

if __name__ == "__main__":
    with open("runtime_quality_map.pkl", "rb") as f:
        runtime_quality_map = pickle.load(f)

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

    circuit = "mcml"

    current_circuit_path = os.path.abspath(os.path.join(
        benchmark_basepath,
        circuit
    ))

    inner_num_reference = 1

    target_path_ref = os.path.abspath("./tmp/ref")
    target_path_cnn = os.path.abspath("./tmp/cnn")

    eval_type(
        current_circuit_path, circuit, target_path_ref, "reference",
        inner_num_reference, inner_num_reference
    )

    eval_type(
        current_circuit_path, circuit, target_path_cnn, "cnn",
        inner_num_reference * cnn_inner_num_factor, inner_num_reference
    )
