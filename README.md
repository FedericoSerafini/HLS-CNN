# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work:
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 instead of Vivado HLS version 2018.3.

## Project summary:

[FS presentation](/HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).

## Workflow and project structure:

[Python](Code/Python):
  
1.  model definition, training and evaluation;
2.  export of (trained) network weights and architecture through C header files.

[Headers](Code/Headers):

3.  C header files containing network architecture and weights.

[C](Code/C):

4.  replication of the trained network in C (using previously-generated headers).

[Vitis HLS](Code/Vitis-HLS):

5.  replication of the network in C++ using Vitis HLS syntax constructs and libraries.
