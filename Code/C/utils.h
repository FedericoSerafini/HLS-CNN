#pragma once

#include "definitions.h"

#include "stdio.h"
#include <stdint.h>

int
read_img(const char * file, float img [IMG_ROWS][IMG_COLS]);

void
normalize (
  float   img_in  [IMG_ROWS][IMG_COLS],
  float img_out [IMG_ROWS][IMG_COLS]
);

void
padding(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [IMG_ROWS + 2][IMG_COLS + 2]
);

void
print_img(float img[IMG_ROWS][IMG_COLS]);

void
print_pad_img(float img[IMG_ROWS + 2][IMG_COLS + 2]);

