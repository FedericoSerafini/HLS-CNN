# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 instead of Vivado HLS version 2018.3.

## Summary

Project presentations for the "Embedded Systems" Master course at University of Parma:
[FS presentation](Paper/HLS-CNN-presentation-FS.pdf) and [GB presentation](Paper/HLS-CNN-presentation-GB.pdf).

## Workflow and code structure

### Data:

0. Input images.

### Python:
  
1.  model definition, training and evaluation;
2.  export of (trained) network weights and architecture through C header files.

### Headers:

3.  C header files containing network architecture and weights.

### C:

4.  replication of the trained network in C (using previously-generated headers).

### Vitis HLS:

5.  translation from C to C++ and code refactoring to take advantage of Vitis HLS pragma and directives.

## Warning
C/C++ code of this project is designed to generate an RTL description that meets ambitious performance requirements through pipelining and parallelism;
to achieve this, we wrote specific and non-parametric code,
meaning that changes to the network architecture are **not automatically** propagated to the rest of the project.
