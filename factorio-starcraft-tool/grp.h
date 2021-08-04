#pragma once
#include <cstdint>
#include <vector>

#include "../CImg/CImg.h"

struct FRAME {
  std::uint32_t unkn1;
  std::uint16_t wdt;
  std::uint16_t hgt;
  std::uint32_t size;
};

struct GROUP {
  std::uint32_t dwFlesize;
  std::uint16_t wFrames;
  std::uint16_t wFlags;
};

std::vector<cimg_library::CImg<std::uint8_t>> loadGrp(const std::vector<std::uint8_t>& data, const std::vector<int>& requested_indices);
