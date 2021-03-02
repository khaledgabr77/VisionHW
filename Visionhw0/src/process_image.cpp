#include "image.h"
#include <assert.h>
#include <iostream>
#include <string.h>
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

void set_pixel(image im, int x, int y, int c, float v) {
  if ((x >= 0 && x < im.w) && (y >= 0 && y < im.h) && (c >= 0 && c < im.c)) {
    im.data[x + y * im.w + im.w * im.h * c] = v;
  }
}

image copy_image(image im) {
  image copy = make_image(im.w, im.h, im.c);
  // TODO Fill this in
  memcpy(copy.data, im.data, im.h * im.c * im.w * sizeof(float));

  return copy;
}

image rgb_to_grayscale(image im) {
  assert(im.c == 3);
  image gray = make_image(im.w, im.h, 1);
  // TODO Fill this in
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      gray.data[x + y * im.w] = 0.299 * im.data[x + im.w * y] +
                                0.587 * im.data[x + y * im.w + im.h * im.w] +
                                0.114 * im.data[x + y * im.w + im.w * im.h * 2];
    }
  }

  return gray;
}