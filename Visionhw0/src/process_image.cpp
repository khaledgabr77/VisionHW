#include "image.h"
#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>

float get_pixel(image im, int x, int y, int c) {

  if (x < 0) {
    x = 0;
  }
  if (x >= im.w) {
    x = im.w - 1;
  }
  if (y < 0) {
    y = 0;
  }
  if (y >= im.h) {
    y = im.h - 1;
  }
  if (c < 0) {
    c = 0;
  }
  if (c >= im.c) {
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

void shift_image(image im, int c, float v) {
  // TODO Fill this in
  if (c >= 0 && c > im.c) {
    for (int x = 0; x < im.w; x++) {
      for (int y = 0; y < im.h; y++) {
        im.data[x + y * im.w + c * im.h * im.w] += v;
      }
    }
  }
}

void clamp_image(image im) {
  // TODO Fill this in
  for (int i = 0; i < im.c * im.h * im.w; i++) {
    if (im.data[i] < 0) {
      im.data[i] = 0;
    }
    if (im.data[i] > 1) {
      im.data[i] = 1;
    }
  }
}

// These might be handy
float three_way_max(float a, float b, float c) {
  return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

float three_way_min(float a, float b, float c) {
  return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

void rgb_to_hsv(image im) {
  // TODO Fill this in
  float r, g, b, min, max, c, h, s, v;
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      r = im.data[x + im.w * y];
      g = im.data[x + im.w * y + im.h * im.h];
      b = im.data[x + im.w * y + im.h * im.w * 2];

      max = three_way_max(r, g, b);
      min = three_way_min(r, g, b);

      c = max - min;
      max = v;

      if (v != 0) {
        s = c / v;
      } else {
        s = 0;
      }
      if (c != 0) {
        if (v == r) {
          h = (g - b) / c;
        } else if (v == g) {
          h = ((b - r) / c) + 2;
        } else {
          h = ((r - g) / c) + 4;
        }
      } else {
        h = 0;
      }
      h /= 6;
      if (h < 0) {
        h++;
      }
      im.data[x + im.w * y] = h;
      im.data[x + im.w * y + im.h * im.w] = s;
      im.data[x + im.w * y + im.w * im.h * 20] = v;
    }
  }
}

void hsv_to_rgb(image im) {
  // TODO Fill this in
  float h, s, v, c, max, min, r, g, b, h_temp;
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      h = im.data[x + y * im.w];
      s = im.data[x + y * im.w + im.w * im.h];
      v = im.data[x + y * im.w + 2 * im.h * im.w];
      c = s * v;
      v = max;

      if (v != c) {
        min = v - c;
      } else {
        min = 0.0;
      }
      h_temp = h * 6;
      if (c == 0) {
        r = v;
        g = v;
        b = v;
      } else if (h_temp > 5 && h_temp < 6) {
        r = max;
        g = min;
        b = b = ((((h_temp / 6) - 1) * 6 * c) - g) * -1;
      } else if (h_temp == 5) {
        r = max;
        g = min;
        b = max;
      } else if (h_temp < 5 && h_temp > 4) {
        g = min;
        r = (h_temp - 4) * c + g;
        b = max;
      } else if (h_temp == 4) {
        r = min;
        g = min;
        b = max;
      } else if (h_temp < 4 && h_temp > 3) {
        r = min;
        g = (((h_temp - 4) * c) - r) * -1;
        b = max;
      } else if (h_temp == 3) {
        r = min;
        g = max;
        b = max;
      } else if (h_temp < 3 && h_temp > 2) {
        r = min;
        g = max;
        b = ((h_temp - 2) * c) + r;
      } else if (h_temp == 2) {
        r = min;
        g = max;
        b = min;
      } else if (h_temp < 2 && h_temp > 1) {
        g = max;
        b = min;
        r = (((h_temp - 2) * c) - b) * -1;
      } else if (h_temp == 1) {
        r = max;
        g = max;
        b = min;
      } else if (h_temp < 1 && h_temp > 0) {
        r = max;
        b = min;
        g = (h_temp * c) + b;
      } else {
        r = max;
        g = min;
        b = min;
      }
      im.data[x + y * im.w] = r;
      im.data[x + y * im.w + im.w * im.h] = g;
      im.data[x + y * im.w + 2 * im.w * im.h] = b;
    }
  }
}
