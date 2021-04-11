#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct imagedat_info_t;

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info, const std::string& out_dir, bool is_low);
