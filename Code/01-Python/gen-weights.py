"""CNN weights generator

This program uses a CNN model built with Tensorflow/Keras to compute
the weights that will be used by the C/HLS network.

Produces a set of header files as output: definitions.h, conv_weights.h,
dense_weights.h.

images size: 28x28

"""

from os import path
import pickle
from tensorflow.keras.datasets import mnist
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.utils import plot_model
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D
from tensorflow.keras.layers import ZeroPadding2D
from tensorflow.keras.layers import MaxPooling2D
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import Flatten
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.models import Sequential
from tensorflow.keras.models import load_model
from numpy import empty
from matplotlib import pyplot as plt
import time
import math

# Constants.
input_size       = (28,28)
conv_kernel_size = (7,7)
conv_filter_num  = 4
pool_size        = (2,2)
dense_size       = 10
training_epochs  = 6
pad = int(math.floor(conv_kernel_size[0] / 2))

def load_dataset() -> tuple:
	# Load dataset.
	(trainX, trainY), (testX, testY) = mnist.load_data()
	# Reshape dataset to have a single channel.
	trainX = trainX.reshape((trainX.shape[0], input_size[0], input_size[1], 1))
	testX = testX.reshape((testX.shape[0], input_size[0], input_size[1], 1))
	# One hot encode target values.
	trainY = to_categorical(trainY)
	testY = to_categorical(testY)
	return trainX, trainY, testX, testY

def prep_pixels(train, test) -> tuple:
	# Convert from integers to floats.
	train_norm = train.astype('float32')
	test_norm = test.astype('float32')
	# Normalize to range 0-1.
	train_norm = train_norm / 255.0
	test_norm = test_norm / 255.0
	# Return normalized images.
	return train_norm, test_norm

def define_model() -> Sequential:
	# Define model.
	model = Sequential()
	model.add(ZeroPadding2D(padding=pad, input_shape=(input_size[0], input_size[1], 1), name='padding_layer'))
	model.add(Conv2D(conv_filter_num, conv_kernel_size, activation='relu', padding='valid', kernel_initializer='he_uniform', input_shape=(30, 30, 1), name='convolution_layer'))
	model.add(MaxPooling2D(pool_size, name='max_pooling_layer'))
	model.add(Flatten(name='flatten_layer'))
	model.add(Dense(10, activation='softmax', name='dense_layer'))
	# Compile model.
	model.compile(optimizer=Adam(), loss='categorical_crossentropy', metrics=['accuracy'])
	# Return model.
	return model

def plot_history(history: dict) -> None:
	# Summarize history for accuracy.
	#plt.grid()
	plt.gca().yaxis.grid(True)
	plt.plot(history['accuracy'])
	plt.plot(history['val_accuracy'])
	plt.title('Model accuracy')
	plt.ylabel('Accuracy')
	plt.xlabel('Epoch')
	plt.xticks(range(0, training_epochs, 1))
	plt.legend(['Train', 'Validation'], loc='center right')
	plt.savefig('history_accuracy.png')
	# Summarize history for loss.
	plt.cla()
	#plt.grid()
	plt.gca().yaxis.grid(True)
	plt.plot(history['loss'])
	plt.plot(history['val_loss'])
	plt.title('Model loss')
	plt.ylabel('Loss')
	plt.xlabel('Epoch')
	plt.xticks(range(0, training_epochs, 1))
	plt.legend(['Train', 'Validation'], loc='center right')
	plt.savefig('history_loss.png')


def gen_conv_params(layer:Conv2D,
		label:str, kr:str, kc:str, f:str) -> str:
	'''
	Takes a Conv2D layer as input and returns a C initialization (as a
	string) of '(label)_weights[kr][kc][f]' and '(label)_biases[f]'
	arrays.
	'''

	w, b = layer.weights
	res = ''

	# Conversion of weights array.
	new_w = empty(shape=(w.shape[3],w.shape[0],w.shape[1]))
	for row in range(w.shape[0]):
		for col in range(w.shape[1]):
			for filter in range(w.shape[3]):
				new_w[filter][row][col] = w[row][col][0][filter]
	w = new_w

	# Weights: (label)_weights[kr][kc][f].
	res += '// ' + label.capitalize() + ' layer weights.\n'
	res += 'float ' + label + '_weights [' + f + '][' + kr + '][' \
			+ kc + ']\n\t= {\n'
	for filter in range(w.shape[0]):
		res += '\t\t\t{\n'
		for row in range(w.shape[1]):
			res += '\t\t\t\t{ '
			for col in range(w.shape[2]):
				res += str(float(w[filter][row][col]))
				if (col != w.shape[2]-1):
					res += ', '
			res += ' }'
			if(row != w.shape[1] -1):
				res += ','
			res += '\n'
		res += '\t\t\t}'
		if(filter != w.shape[0] -1):
			res += ','
		res += '\n'
	res +='\t\t};\n\n'

	# Biases: (label)_biases[f].
	res += '// ' + label.capitalize() + ' layer biases.\n'
	res += 'float ' + label + '_biases [' + f + '] = { '
	for i in range(b.shape[0]):
		res += str(float(b[i]))
		if (i != b.shape[0]-1):
			res += ', '
	res += ' };'

	return res

def gen_dense_params(layer:Dense,
		label:str, size0: str, size1: str) -> str:
	'''
	Takes a Dense layer as input and returns a C initialization (as a
	string) of '(label)_weights[size0][size1]' and '(label)_biases[size1]'
	arrays.
	'''

	w, b = layer.weights
	res = ''

	# Conversion of weights array.
	pool_img_r = int(input_size[0]/pool_size[0])
	pool_img_c = int(input_size[1]/pool_size[1])

	tmp = empty(shape=(pool_img_r, pool_img_c, conv_filter_num, dense_size))
	index = 0
	for i in range(pool_img_r):
		for j in range(pool_img_c):
			for f in range(conv_filter_num):
				for d in range(dense_size):
					tmp[i][j][f][d] = w[index][d]
				index += 1
	index = 0
	new_w = empty(w.shape)
	for f in range(conv_filter_num):
		for i in range(pool_img_r):
			for j in range(pool_img_c):
				for d in range(dense_size):
					new_w[index][d] = tmp[i][j][f][d]
				index += 1
	w = new_w

	# Weights: (label)_weights[size0][size1].
	res += '// ' + label.capitalize() + ' layer weights.\n'
	res += 'float ' + label + '_weights[' + size0 + '][' + size1 + ']\n\t = {\n'
	for i in range(w.shape[0]):
		res += '\t\t\t{ '
		for j in range(w.shape[1]):
			res += str(float(w[i][j]))
			if j != w.shape[1] - 1:
				res += ', '
		res += ' }'
		if i != w.shape[0] - 1:
			res += ','
		res += '\n'
	res += '\t\t};\n\n'

	# Biases : (label)_biases[size1].
	res += '// ' + label.capitalize() + ' layer biases.\n'
	res += 'float ' + label + '_biases [' + size1 + '] = { '
	for i in range(b.shape[0]):
		res += str(float(b[i]))
		if (i != b.shape[0]-1):
			res += ', '
	res += ' };'

	return res

def save_param_on_files(model: Sequential) -> None:
	'''
	Saves model constants and layers parameter of the sequential
	model 'model'.
	Writes on 'definitions.h', 'conv_weights.h' ,'dense_weights.h' files.
	'''

	# definitions.h
	with open('../03-Headers/definitions.h', 'w') as f:
		print('writing \'definitions.h\' file... ', end='')
		print('/*\n * This file is auto-generated by gen-weights.py\n */\n',file=f)
		print('#pragma once', file=f)
		print('\n#define DIGITS 10\n\n#define IMG_ROWS '
			+str(input_size[0])+'\n#define IMG_COLS '+str(input_size[1])+'\n',file=f)
		# Padding.
		print('// Padding.',file=f)
		print( ''
			+ '#define	PAD_ROWS (KRN_ROWS - 1)\n'
			+ '#define	PAD_COLS (KRN_COLS - 1)\n'
			+ '#define PAD_IMG_ROWS (IMG_ROWS + PAD_ROWS)\n'
			+ '#define PAD_IMG_COLS (IMG_COLS + PAD_COLS)\n'
			, file=f)
		# Conv.
		print('// Convolutional layer.',file=f)
		print('#define KRN_ROWS\t',end='',file=f)
		print(str(conv_kernel_size[0]), file=f)
		print('#define KRN_COLS\t',end='',file=f)
		print(str(conv_kernel_size[1]), file=f)
		print('#define FILTERS\t',end='',file=f)
		print(conv_filter_num, file=f, end='\n\n')
		# Pool.
		print('// Pool layer.\n'
			+ '#define POOL_ROWS\t' + str(pool_size[0]) + '\n'
			+ '#define POOL_COLS\t' + str(pool_size[1]) + '\n'
			+ '#define POOL_IMG_ROWS (IMG_ROWS / POOL_ROWS)\n'
			+ '#define POOL_IMG_COLS (IMG_COLS / POOL_COLS)\n'
			, file=f)
		# Flatten.
		print('// Fatten layer.\n'
			+ '#define FLAT_SIZE (FILTERS * POOL_IMG_ROWS * POOL_IMG_COLS)\n'
			, file=f)
		# Dense.
		print('// Dense layers.\n'
			#+ '#define DENSE1_SIZE ' + str(dense_1_size) + '\n'
			+ '#define DENSE_SIZE ' + str(dense_size)
			, file=f
		)
		print('done.')

	# conv_weights.h
	conv_layer = model.layers[1]
	assert(isinstance(conv_layer, Conv2D))

	with open('../03-Headers/conv_weights.h', 'w') as f:
		print('writing \'conv_weights.h\' file... ', end='')
		print('/*\n * This file is auto-generated by gen-weights.py\n */\n',file=f)
		print('#pragma once\n\n#include "definitions.h"\n\n',file=f)
		arrays_def_str = gen_conv_params(conv_layer, 'conv',
			'KRN_ROWS', 'KRN_COLS', 'FILTERS')
		print(arrays_def_str, file=f)
		print('done.')

	# dense_weights.h
	dense_layer = model.layers[4]
	assert(isinstance(dense_layer, Dense))

	with open('../03-Headers/dense_weights.h', 'w') as f:
		print('writing \'dense_weights.h\' file... ', end='')
		print('/*\n * This file is auto-generated by gen-weights.py\n */\n',file=f)
		print('#pragma once\n\n#include "definitions.h"\n\n', file=f)

		arrays_def_str = gen_dense_params(dense_layer, 'dense',
			'FLAT_SIZE', 'DENSE_SIZE')
		print(arrays_def_str, file=f)
		print('done.')

def main() -> None:

    # Load dataset.
	trainX, trainY, testX, testY = load_dataset()
	print('trainX.shape = ', trainX.shape)
	print('trainY.shape = ', trainY.shape)
	print('testX.shape = ', testX.shape)
	print('testY.shape = ', testY.shape)
	# Normalize input images.
	trainX, testX = prep_pixels(trainX, testX)

	# If a trained model is already available: load it.
	# Else: define a new model, train and save it.
	# if not path.isfile('model.h5'):
		# print('model not found: create and train it')
	model = define_model()
	#history = model.fit(trainX, trainY, epochs=5, batch_size=32, validation_data=(testX, testY), verbose=1)
	history = model.fit(trainX,trainY, epochs=training_epochs, batch_size=32, validation_split=0.2, shuffle=True, verbose=1)
	# Save model.
	model.save("model.h5")
	# Save training history.
	with open('train_history_dict', 'wb') as f:
		pickle.dump(history.history, f)

	# 	print('model saved as \'model.h5\'')
	# else:
	# 	print('found a model: use it.')
	# 	model = load_model('model.h5')

	# Print summary.
	print(model.summary())

	# Evaluate model.
	_, acc = model.evaluate(testX, testY, verbose=0)
	print('Accuracy: %.3f' % (acc * 100.0))

	# Computation time of a prediction.
	time_ms_sum = 0
	num_predictions = int(testX.shape[0]/100)
	for i in range(num_predictions):
		print('Making some prediction to measure time taken...'
			+ str(i+1) + '/' + str(num_predictions), end='\r')
		start = time.time()
		model.predict(testX[i].reshape(1, 28, 28, 1),verbose=0)
		end = time.time()
		time_ms_sum += (end - start) * 1000
	time_ms = time_ms_sum / num_predictions
	print()
	print('Mean time taken for a prediction: ' + str(round(time_ms, 4)) + ' ms')

	# Plot model in model.png.
	plot_model(model, 'model.png', show_layer_activations=True,
		show_shapes=True, show_dtype=True, rankdir='TB', dpi=100)

	# Save model summary and accuracy in model.txt.
	with open('model.txt', 'w') as f:
		model.summary(print_fn=lambda x: f.write(x + '\n'))
		print('\nAccuracy on test set: %.3f' % (acc * 100.0), file=f)
		print('\nMean time taken for a prediction: ' + str(round(time_ms, 4))
			+ ' ms', file=f)

	# Load training history and plot.
	history = pickle.load(open('train_history_dict', "rb"))
	plot_history(history)

	# Save parameters and weights on header files.
	save_param_on_files(model)


if __name__ == '__main__':
	main()
