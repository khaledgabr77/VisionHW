#include "image.h"
#include <math.h>

float nn_interpolate(image im, float x, float y, int c) {
  return get_pixel(im, round(x), round(y), c);
}

image nn_resize(image im, int w, int h) {
  image ret = make_image(w, h, im.c);
  float a_x = (float)im.w / w;
  float a_y = (float)im.h / h;
  float b_x = -0.5 + 0.5 * a_x;
  float b_y = -0.5 + 0.5 * a_y;
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      for (int c = 0; c < im.c; c++) {
        float x_new = a_x * x + b_x;
        float y_new = a_y * y + b_y;
        ret.data[x + y * w + c * w * h] = nn_interpolate(im, x_new, y_new, c);
      }
    }
  }
  return ret;
}

float bilinear_interpolate(image im, float x, float y, int c) {
  // TODO

  return 0;
}

image bilinear_resize(image im, int w, int h) {
  // TODO
  return make_image(1, 1, 1);
}
