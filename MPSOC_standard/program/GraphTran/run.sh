#!/bin/bash
../../MPSOC/sim-outorder \
-redir:EM ./datasets/t0.out \
-redir:sim ./sysout/sysinfo.txt \
-redir:SIM_time ./sysout/end_time.txt \
-redir:SIM_visited ./sysout/visited.txt \
-redir:SIM_trace ./sysout/link_trace.txt \
-redir:SIM_package_send ./sysout/package_src_dst.txt \
-config ./config_mesh_ooo33 -max:barrier 0 -max:inst 1000000000000000 G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC G.BNC
