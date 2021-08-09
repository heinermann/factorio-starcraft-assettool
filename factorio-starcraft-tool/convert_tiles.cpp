#include "convert_tiles.h"

#include <vector>
#include <array>
#include <cstdint>
#include <random>

#include "../CImg/CImg.h"

#include "grp.h"
#include "tile_predefs.h"
#include "cimg_extensions.h"
#include "cimg_utils.h"

CImg create_background(std::vector<CImg>& tiles) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> rand_normal_tile(0, 6);
  std::uniform_int_distribution<> rand_variation_tile(7, 12);
  std::uniform_real_distribution<> rand_variation_percent(0, 100);

  int width = tiles[0].width();
  int height = tiles[0].height();

  CImg result(width * 32, height * 32, 1, 4);
  for (int y = 0; y < 32; ++y) {
    int tile_id = 0, last_tile_id = -1;
    for (int x = 0; x < 32; ++x) {
      
      int attempts = 0;
      do {
        tile_id = rand_variation_percent(gen) >= 4.0 ? rand_normal_tile(gen) : rand_variation_tile(gen);
        attempts++;
      } while (tile_id == last_tile_id || attempts > 10);
      last_tile_id = tile_id;

      draw_image(result, width * x, height * y, tiles[tile_id], 0, 0, width, height);
    }
  }
  return result;
}

CImg create_tilesheet(std::vector<CImg>& tiles) {
  int width = tiles[0].width();
  int height = tiles[0].height();

  CImg result(width * 13, height, 1, 4);
  for (int i = 0; i < 13; ++i) {
    draw_image(result, width * i, 0, tiles[i], 0, 0, width, height);
  }
  return result;
}

void convert_vr4_tiles(const std::vector<std::uint8_t>& vr4_data, const std::string& out_dir) {
  std::vector<CImg> tiles = loadGrp(vr4_data, vr4_creep_tiles);

  for (CImg& tile : tiles) {
    BGRAtoRGBA(tile);
  }

  CImg main_tiles = create_tilesheet(tiles);
  std::string main_path = out_dir + "/creep_main.png";
  cimg_library::save_png(main_tiles, main_path.c_str());

  CImg bg_tiles = create_background(tiles);
  std::string bg_path = out_dir + "/creep_background.png";
  cimg_library::save_png(bg_tiles, bg_path.c_str());
}
