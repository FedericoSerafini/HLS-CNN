# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 instead of Vivado HLS version 2018.3.

## Summary

Project presentation for the "Embedded Systems" Master course in University of Parma:
[FS presentation](/HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).

## Workflow and project structure

[Python](Code/Python)
  
1.  model definition, training and evaluation;
2.  export of (trained) network weights and architecture through C header files.

[Headers](Code/Headers)

3.  C header files containing network architecture and weights.

[C](Code/C):

4.  replication of the trained network in C (using previously-generated headers).

[Vitis HLS](Code/Vitis-HLS)

5.  C to C++ code adaptation to take advantage of Vitis HLS syntax constructs and libraries.

## Warning
C/C++ code of this project is designed to generate an RTL description that meets ambitious performance requirements through pipelining and parallelism;
to achieve this objective, we wrote specific and non-parametric code,
meaning that most of the changes that can be applied to the network architecture are **not automatically** propagated to the rest of the project.
