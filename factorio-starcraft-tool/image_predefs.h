#pragma once
#include <vector>

struct imagedat_info_t {
  int id;
  bool draw_as_glow;
  bool draw_as_shadow;
  bool gfx_turns;
  bool vertical_frames;
};

extern std::vector<imagedat_info_t> image_predefs;
