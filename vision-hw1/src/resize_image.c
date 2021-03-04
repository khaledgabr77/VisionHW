#include "image.h"
#include <math.h>

float nn_interpolate(image im, float x, float y, int c) {
  // TODO Fill in

}

image nn_resize(image im, int w, int h) {
  // TODO Fill in (also fix that first line)

}

float bilinear_interpolate(image im, float x, float y, int c) {
  // TODO
  return 0;
}

image bilinear_resize(image im, int w, int h) {
  // TODO
  return make_image(1, 1, 1);
}
