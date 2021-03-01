#include "image.h"
#include <iostream>
#include <string>

float get_pixel(image im, int x, int y, int c) {

  if (x < 0) {
    x = 0;
  } else if (x >= im.w) {
    x = im.w - 1;
  } else if (y < 0) {
    y = 0;
  } else if (y >= im.h) {
    y = im.h - 1;
  } else if (c < 0) {
    c = 0;
  } else if (c >= im.c) {
    c = im.c - 1;
  }

  return im.data[x + y * im.w + im.w * im.h * c];
}
