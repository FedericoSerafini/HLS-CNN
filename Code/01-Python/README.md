# Python

## Pre-requisites

- (Optionally) Create new virtual environment (e.g. named `my-venv`):
    ```
    python3 -m venv my-venv
    ```
    and activate it:
    ```
    source my-venv/bin/activate
    ```
    To deactivate the virtual environment:
    ```
    deactivate
    ```

- Install Python's packages required:
    ```
    pip install -r requirements.txt
    ```

- Install graphviz:
    ```
    sudo apt install graphviz
    ```

## Train network and export weights: `gen-weights.py`

This program uses a CNN model built with Tensorflow/Keras to compute
the weights that will be used by the HLS network.

Produces a set of header files in `03-Headers/` directory:
- `conv_weights.h`
- `dense_weights.h`
- `definitions.h`

Also, this program produces/saves:
- plots of training history (`history_accuracy.png` and `history_loss.png`);
- the Keras model created (`model.h5`);
- the Keras model summary (`model.txt`);
- the Keras model architecture plot (`model.png`);
- a dictionary of training history (`train_history_dict`).

### Usage

```
python3 gen-weights.py
```

## Generate input/output for HLS testbench: `gen-tb.py`

This program generates the files `in.dat` and `out.dat` in `../02-Data/`
directory for the HLS test-bench (`cnn_tb.c`). It takes the
[MNIST-tensorflow](https://www.tensorflow.org/datasets/catalog/mnist)
test-set and generate the files in this format:

- `in.dat`:
    ```
    image_0
    (blank line)
    image_1
    (blank line)
    ....
    image_N
    ```

    where each image is a list of pixel with integer value from 0 to 255:

    ```
    pixel_0_0   pixel_0_1   ... pixel_0_28
    pixel_1_0   pixel_1_1   ... pixel_1_28
    ...         ...         ...
    pixel_28_0  pixel_28_1  ... pixel_28_28
    ```

- `out.dat`:
    ```
    label_y_0
    label_y_1
    ...
    label_y_N
    ```

### Usage

```
python3 gen-tb.py
```
