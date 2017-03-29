# A simplescalar based simulator formpsoc
## MPSoC Simulator
This is a MPSoc Simulator on linux. **Please note that, In this repository I just modified a little source code, many files were created and modified by my "tutor".  :)**
***
## What is MPSoC
[MPSoC Wiki](https://en.wikipedia.org/wiki/MPSoC)

The multiprocessor system-on-chip (MPSoC) is a system-on-a-chip (SoC) which uses multiple processors (see multi-core), usually targeted for embedded applications. It is used by platforms that contain multiple, usually heterogeneous, processing elements with specific functionalities reflecting the need of the expected application domain, a memory hierarchy (often using scratchpad RAM and DMA) and I/O components. All these components are linked to each other by an on-chip interconnect. These architectures meet the performance needs of multimedia applications, telecommunication architectures, network security and other application domains while limiting the power consumption through the use of specialised processing elements and architecture.

---
You'd better use these with gcc-4.8.1 and gdb-7.6.

"MPSOC_beta.tar.gz" contains MPSOC64, MPSOC256, TEST64 and TEST256. MPSOC64 and MPSOC256 are simulators. TEST64 and TEST256 are their samples or tests files.
"MPSOC_standard.tar.gz" demonstrates a graph traverse application.
The above two can all begin with executing "run.sh".

"py_graph.tar.gz" contains some python scripts that processing graph files for graph traverse.
gxp added frequency adjustment in "MPSOC_add_frequency".
"tgff-3_4.tgz" is a tool for generating graphs.
"Chaco-2.2.tar.gz" is a tool for partition the graph.

You can see files in "docs" for more information.
