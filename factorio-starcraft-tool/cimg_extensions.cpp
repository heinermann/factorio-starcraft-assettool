#include "cimg_extensions.h"

#include <memory>
#include <iostream>

#include "../CImg/CImg.h"
#include "../fpng/src/fpng.h"
#include "../fpng/src/lodepng.h"

namespace cimg_library {
  extern "C" {
    void save_png(const CImg<std::uint8_t> img, const char* const filename) {
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
  }
}
