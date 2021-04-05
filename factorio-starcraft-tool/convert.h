#pragma once

#include <vector>
#include <cstdint>

struct imagedat_info_t;

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info);
