#include "convert_tiles.h"

#include <vector>
#include <array>
#include <cstdint>

#include "../CImg/CImg.h"

#include "grp.h"
#include "tile_predefs.h"
#include "cimg_extensions.h"
#include "cimg_utils.h"


void convert_vr4_tiles(const std::vector<std::uint8_t>& vr4_data, const std::string& out_dir) {
  std::vector<CImg> tiles = loadGrp(vr4_data, vr4_creep_tiles);

  for (CImg& tile : tiles) {
    BGRAtoRGBA(tile);
  }

  std::array<char, 128> filename;
  for (int i = 0; i < tiles.size(); ++i) {
    std::snprintf(filename.data(), filename.size(), "%s/creep_%04d.png", out_dir.c_str(), i);
    cimg_library::save_png(tiles[i], filename.data());
  }
}
