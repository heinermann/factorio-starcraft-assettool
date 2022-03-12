#include "cimg.h"

#include <algorithm>
#include <memory>
#include <iostream>

#include "../CImg/CImg.h"
#include "../fpng/src/fpng.h"
#include "../fpng/src/lodepng.h"

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

// TODO: Optimize with memcpy (note CImg channels are separate from each other)
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

void save_png(const CImg& img, const char* const filename) {
  // Convert image to have interleaved channels rather than CImg's separate channels
  auto img_data = std::make_unique<std::uint8_t[]>(img.size());
  cimg_forXYC(img, x, y, c) {
    img_data[y * img.width() * img.spectrum() + x * img.spectrum() + c] = img(x, y, c);
  }

  // Save the image
  if (img.spectrum() == 3 || img.spectrum() == 4) {
    if (!fpng::fpng_encode_image_to_file(filename, img_data.get(), img.width(), img.height(), img.spectrum())) {
      std::cerr << "Failed to encode \"" << filename << "\" (fpng)" << std::endl;
    }
  }
  else if (img.spectrum() == 2) {
    if (int errcode = lodepng_encode_file(filename, img_data.get(), img.width(), img.height(), LodePNGColorType::LCT_GREY_ALPHA, 8)) {
      std::cerr << "Failed to encode \"" << filename << "\" (lodepng) error code = " << errcode << std::endl;
    }
  }
  else {
    std::cerr << "Failed to encode \"" << filename << "\" (format not supported) format = " << img.spectrum() << std::endl;
  }
}
