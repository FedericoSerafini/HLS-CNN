# HLS-CNN
High Level Synthesis of a trained Convolutional Neural Network for
handwritten digit recongnition.

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

For additional information look at [FS presentation](/HLS-CNN-presentation-FS.pdf) and [GB presentation](HLS-CNN-presentation-GB.pdf).
