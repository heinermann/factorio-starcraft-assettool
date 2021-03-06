#pragma once
#include <cstdint>
#include <vector>
#include <optional>

#include "cimg.h"

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

std::vector<CImg> loadGrp(const std::vector<std::uint8_t>& data, const std::optional<std::vector<int>>& requested_indices = std::nullopt);
