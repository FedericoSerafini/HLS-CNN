# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 ([patched](https://support.xilinx.com/s/article/76960?language=en_US)).

## Slides

Project presentations for the "Embedded Systems" master course at University of Parma:
[FS presentation](HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).

## Code structure and workflow

If you are not iterested in fiddling with the network architecture and you just want to try to export an RTL description as IP,
you can ignore the steps from 1 to 4 and jump directly to step 5 to generate the Vitis-HLS project
(the use of Python code is not strictly necessary because a the Python-generated output is already present in
```Code/02-Data``` and ```Code/03-Headers``` folders).

### ```Code/01-Python```:

Contains Python source code to do:
-  Model definition, training and evaluation.
-  Exportation of (trained) network weights and architecture through C header files.
-  Generation of input and expected output for HLS testbench.

### ```Code/02-Data```:

-  Training images (generated using Python).

### ```Code/03-Headers```:

-  C header files containing network architecture and weights (generated using Python).

### ```Code/04-C```:

-  Replication of the trained network in C (using headers in ```Code/03-Headers```).

### ```Code/05-Vitis-HLS```:

-  Translation from C to C++ and code refactoring to take advantage of Vitis HLS pragma and directives.

## Future work
-  Find a way to share the input image between the different streams instead of duplicating it;
this will reduce the memory requirements of the target board.
- Improve network architecture to reduce hardware requirements without sacrificing performances and/or accuracy.

## Warning
C/C++ code of this project is designed to generate an RTL description that meets ambitious performance requirements through pipelining and parallelism.
To achieve this objective, we wrote specific and non-parametric code and, as a consequence, non-trvial changes to the network architecture (such as adding or removing layers) are **not automatically** propagated to the rest of the project.
