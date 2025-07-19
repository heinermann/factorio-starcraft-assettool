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
  cimg_forXY(img, x, y) {
    result(hm1 - y, x, 0, 0) = 0;
    result(hm1 - y, x, 0, 1) = img(x, y, 0, 3);
  }
  return result;
}

void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, int src_x, int src_y, int width, int height) {
  int channels = std::min(dst.spectrum(), src.spectrum());
  for (int y = 0; y < height; ++y) {
    for (int c = 0; c < channels; ++c) {
      memcpy(dst.data(dst_x, dst_y + y, 0, c), src.data(src_x, src_y + y, 0, c), width);
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
  int total_size = img.width() * img.height();
  int run_length = 0;

  std::uint8_t* a_data = img.data(0, 0, 0, img.spectrum() - 1);

  for (int i = 0; i < total_size;) {
    while (a_data[i + run_length] == 0 && i + run_length < total_size) {
      run_length++;
    }

    for (int c = 0; c < img.spectrum() - 1; ++c) {
      std::memset(&img.data(0, 0, 0, c)[i], 0, run_length);
    }

    i += run_length;
    run_length = 0;
    while (a_data[i] != 0 && i < total_size) {
      i++;
    }
  }
}

CImg load_png(const char* const filename) {
  std::vector<std::uint8_t> data;
  std::uint32_t width, height, channels;
  if (fpng::fpng_decode_file(filename, data, width, height, channels, 4) != 0) {
    std::cerr << "Failed to decode \"" << filename << "\" (fpng)" << std::endl;
    return {};
  }

  if (channels != 4) {
    std::cerr << "Unexpected number of channels (fpng)" << std::endl;
    return {};
  }
  
  CImg result(width, height, 1, channels);
  for (unsigned i = 0; i < data.size(); i += 4) {
    unsigned x = (i / 4) % width, y = (i / 4) / width;
    result(x, y, 0, 0) = data[i];
    result(x, y, 0, 1) = data[i + 1];
    result(x, y, 0, 2) = data[i + 2];
    result(x, y, 0, 3) = data[i + 3];
  }
  return result;
}

void save_png(const CImg& img, const char* const filename) {
  // Convert image to have interleaved channels rather than CImg's separate channels
  auto img_data = std::make_unique<std::uint8_t[]>(img.size());
  std::cout << "BEFORE" << std::endl;
  cimg_forXYC(img, x, y, c) {
    img_data[y * img.width() * img.spectrum() + x * img.spectrum() + c] = img(x, y, c);
  }
  std::cout << "BEFORE 2" << std::endl;

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
  std::cout << "END" << std::endl;

}
