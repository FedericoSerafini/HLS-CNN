#pragma once

#include "definitions.h"

float dense1_weights[FLAT_SIZE * DENSE1_SIZE];

float dense1_biases[DENSE1_SIZE];

float dense2_weights[DENSE1_SIZE * DENSE2_SIZE];

float dense2_biases[DENSE2_SIZE];
