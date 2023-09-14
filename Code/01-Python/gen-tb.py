'''
This program generates in.dat and out.dat for cnn_tb.c starting from
the images of MNIST test set.

out.dat:
    label_y_0
    label_y_1
    ...
    label_y_N

in.dat:
    image_0
    (blank line)
    image_1
    (blank line)
    ....
    image_N
'''

from tensorflow.keras.datasets import mnist
import numpy as np

# Load dataset.
(_, _), (test_X, test_y) = mnist.load_data()
print('X_test:  '  + str(test_X.shape))
print('Y_test:  '  + str(test_y.shape))

# Number of samples into test set.
N = test_X.shape[0]

# Take all images and labels.
images = test_X[:N]
labels = test_y[:N]

# Print on files.
in_dat=''
out_dat=''
for i in range(N):
    label = labels[i]
    pixels = images[i]
    pixels = np.array(pixels.reshape((28,28)))
    for x in range(pixels.shape[0]):
        in_dat += ' '.join(
            [str(pixels[x][y]) for y in range(pixels.shape[1])])
        in_dat += '\n'
    in_dat += '\n'
    out_dat += str(label) + '\n'

with open('../02-Data/in.dat', 'w') as f:
    print(in_dat, file=f, end='')
    print('Written ' + str(N) + ' images in ../02-Data/in.dat')

with open('../02-Data/out.dat', 'w') as f:
    print(out_dat, file=f, end='')
    print('Written ' + str(N) + ' labels in ../02-Data/out.dat')
