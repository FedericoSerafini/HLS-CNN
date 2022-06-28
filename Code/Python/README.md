## gen-weights.py

This program uses a CNN model built with Tensorflow/Keras to compute
the weights that will be used by the HLS network.

Produces a set of header files in `Headers/` directory:
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

## gen-tb.py

This program generates in.dat and out.dat (in the current directory) for
cnn_tb.c starting from first N images of **MNIST test set**.

- in.dat:
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

- out.dat:
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
## Useful info

- To generate new `requirements.txt` file (when `.py` files are modified)


    (if you don't already have `pipreqs` installed)
    ```
    pip install pipreqs
    ```
    Then, in this directory:
    ```
    pipreqs --force
    ```

- To create a virtual environment starting from `requirements.txt` to
run these programs:

    (if you don't already have `virtualenv` installed)
    ```
    pip install virtualenv
    ```
    Then,
    ```bash
    # creates new environment (called 'venv' here)
    virtualenv venv

    # to enter the virtual environment
    source venv/bin/activate

    # to install the requirements in the current environment
    pip install -r requirements.txt
    ```

