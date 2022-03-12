#pragma once

#include "../CImg/CImg.h"

namespace cimg_library {
  extern "C" {
    void save_png(const CImg<std::uint8_t> img, const char* const filename);
  }
}
