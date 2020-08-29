set PATH=%PATH%;$PWD/src/ml_integration/lib/
vpr ../vtr_flow/arch/timing/k6_frac_N10_mem32K_40nm.xml ../vtr_flow/benchmarks/vtr_benchmarks_blif/blob_merge.blif --place --route --inner_num 0.01
PAUSE