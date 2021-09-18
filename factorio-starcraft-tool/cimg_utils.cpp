#include "cimg_utils.h"

#include <algorithm>

CImg get_rotate90_black(const CImg& img) {
  CImg result(img.height(), img.width(), 1, 2);
  int hm1 = img.height() - 1;
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      result(hm1 - y, x, 0, 0) = 0;
      result(hm1 - y, x, 0, 1) = img(x, y, 0, 3);
    }
  }
  return result;
}

void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, int src_x, int src_y, int width, int height) {
  int channels = std::min(dst.spectrum(), src.spectrum());
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < channels; ++c) {
        dst(dst_x + x, dst_y + y, 0, c) = src(src_x + x, src_y + y, 0, c);
      }
    }
  }
}

void BGRAtoRGBA(CImg& img) {
  cimg_forXY(img, x, y) {
    std::swap(img(x, y, 0, 0), img(x, y, 0, 2));
  }
}

// Zeroing out transparent pixels saves a lot of space on all sheets
void zero_out_transparent(CImg& img) {
  cimg_forXY(img, x, y) {
    if (img(x, y, 0, img.spectrum() - 1) != 0) continue;

    for (int c = 0; c < img.spectrum() - 1; ++c)
      img(x, y, 0, c) = 0;
  }
}

void add_alpha_px(CImg& img, int x, int y, std::uint8_t value) {
  if (x >= 0 && y >= 0 && x < img.width() && y < img.height()) {
    img(x, y, 0, 3) = std::min(img(x, y, 0, 3) + value, 255);
  }
}
