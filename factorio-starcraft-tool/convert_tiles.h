#pragma once

#include <vector>
#include <string>
#include <cstdint>

void convert_vr4_tiles(const std::vector<std::uint8_t>& vr4_data, const std::string& out_dir);
void convert_icons(const std::vector<std::uint8_t>& data, const std::string& out_dir);
void convert_cmdicons(const std::vector<std::uint8_t>& data, const std::string& out_dir);
