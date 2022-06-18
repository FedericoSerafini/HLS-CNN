# gen-weights.py

This program uses a CNN model built with Tensorflow/Keras to compute
the weights that will be used by the HLS network.

Produces an header file `weights.h` as output.


## Usage

```
python3 gen-weights.py
```


Useful info:

- To generate `requirements.txt` file:


    (if you don't already have `pipreqs` installed)
    ```
    pip install pipreqs
    ```
    Then, in this directory:
    ```
    pipreqs --force
    ```

- To create a virtual environment starting from `requirements.txt:

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