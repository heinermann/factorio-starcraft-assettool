#pragma once
#include <vector>
#include <unordered_map>

struct imagedat_info_t {
  int id;
  bool draw_as_glow;
  bool draw_as_shadow;
  unsigned gfx_turns_frames;
  bool vertical_frames;
  bool warp_overlay;
  bool flipped;
};


extern const imagedat_info_t WARP_TEXTURE;
extern std::vector<imagedat_info_t> image_predefs;

