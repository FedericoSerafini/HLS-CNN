# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 instead of Vivado HLS version 2018.3.

## Summary

Project presentations for the "Embedded Systems" Master course at University of Parma:
[FS presentation](HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).

## Code structure and workflow

### Data:

-  Input images (generated using Python).

### Python:

Contains Python source code to do:
-  Model definition, training and evaluation.
-  Exportation of (trained) network weights and architecture through C header files.
-  Generation of input and expected output for HLS testbench.

The use of Python code is not strictly necessary: the output of these steps is already present in ```Code/01-Data``` and ```Code/03-Headers``` folders.

### Headers:

-  C header files containing network architecture and weights (generated using Python).

### C:

-  Replication of the trained network in C (using headers in ```Code/03-Headers```).

### Vitis HLS:

-  Translation from C to C++ and code refactoring to take advantage of Vitis HLS pragma and directives.

## Warning
C/C++ code of this project is designed to generate an RTL description that meets ambitious performance requirements through pipelining and parallelism;
to achieve this, we wrote specific and non-parametric code,
meaning that changes to the network architecture are **not automatically** propagated to the rest of the project.
