#include "convert_tiles.h"

#include <vector>
#include <array>
#include <cstdint>
#include <random>

#include "cimg.h"
#include "grp.h"
#include "tile_predefs.h"

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

void convert_vr4_tiles(const std::vector<std::uint8_t>& data, const std::string& out_dir) {
  std::vector<CImg> tiles = loadGrp(data, vr4_creep_tiles);

  for (CImg& tile : tiles) {
    BGRAtoRGBA(tile);
  }

  CImg main_tiles = create_tilesheet(tiles);
  std::string main_path = out_dir + "/creep_main.png";
  save_png(main_tiles, main_path.c_str());

  CImg bg_tiles = create_background(tiles);
  std::string bg_path = out_dir + "/creep_background.png";
  save_png(bg_tiles, bg_path.c_str());
}

void convert_icons(const std::vector<std::uint8_t>& data, const std::string& out_dir) {
  std::vector<CImg> icons = loadGrp(data, icon_indices);

  for (size_t i = 0; i < icons.size(); ++i) {
    BGRAtoRGBA(icons[i]);

    std::string path = out_dir + "/" + std::to_string(i) + ".png";
    save_png(icons[i], path.c_str());
  }
}

void apply_color(CImg& img, int tint_r, int tint_g, int tint_b) {
  cimg_forXY(img, x, y) {
    img(x, y, 0, 0) = std::uint8_t(std::clamp(tint_r * img(x, y, 0, 0) / 131, 0, 255));
    img(x, y, 0, 1) = std::uint8_t(std::clamp(tint_g * img(x, y, 0, 1) / 130, 0, 255));
    img(x, y, 0, 2) = std::uint8_t(std::clamp(tint_b * img(x, y, 0, 2) / 131, 0, 255));
  }
}

void convert_cmdicons(const std::vector<std::uint8_t>& data, const std::string& out_dir) {
  std::vector<CImg> icons = loadGrp(data, cmdicon_indices);

  for (size_t i = 0; i < icons.size(); ++i) {
    BGRAtoRGBA(icons[i]);

    CImg fixed(128, 128, 1, 4, 0);
    int x = (128 - icons[i].width()) / 2;
    int y = (128 - icons[i].height()) / 2;

    draw_image(fixed, x, y, icons[i], 0, 0, icons[i].width(), icons[i].height());

    apply_color(fixed, 255, 255, 57);
    zero_out_transparent(fixed);

    std::string path = out_dir + "/" + std::to_string(cmdicon_indices[i]) + ".png";
    save_png(fixed, path.c_str());
  }
}
