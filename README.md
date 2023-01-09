# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for handwritten digit recongnition.

## Related work:
This project uses many concepts coming from a previous work that can be found [here](https://www.amiq.com/consulting/2018/12/14/how-to-implement-a-convolutional-neural-network-using-high-level-synthesis).
The main difference is that our implementation is written for Vitis HLS version 2020.2 instead of Vivado HLS version 2018.3.

## Project summary:

[FS presentation](/HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).

## Project structure:

[Python](Code/Python):
  
-  model definition, training and evaluation;
-  export of (trained) network weights and architecture using C header files.

[Headers](Code/Headers):

-  C header files containing network architecture and weights.

[C](Code/C):

-  replication of the network in C.

[Vitis HLS](Code/Vitis-HLS):

-  replication of the network in C++ using Vitis HLS syntax constructs and libraries.
