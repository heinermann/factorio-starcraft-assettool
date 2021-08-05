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

  int width = tiles[0].width();
  int height = tiles[0].height();

  CImg main_tiles(width * 13, height, 1, 4);
  for (int i = 0; i < 13; ++i) {
    draw_image(main_tiles, width * i, 0, tiles[i], 0, 0, width, height);
  }

  std::string main_path = out_dir + "/creep_main.png";
  cimg_library::save_png(main_tiles, main_path.c_str());
}
