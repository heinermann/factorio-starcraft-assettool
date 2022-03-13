#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <execution>
#include <random>

#include "../fpng/src/fpng.h"
#include "casc.h"
#include "progress.h"
#include "stopwatch.h"

#include "convert_anim.h"
#include "convert_tiles.h"
#include "image_predefs.h"
#include "sound_predefs.h"

void create_output_dirs() {
  constexpr const char* const out_dirs[] = {
    "graphics/hd",
    "graphics/low",
    "sound",
    "locale",
    "graphics/tiles/hd",
    "graphics/tiles/low",
    "graphics/icons",
    "graphics/cmdicons"
  };

  for (auto dir : out_dirs) {
    std::filesystem::create_directories(dir);
  }
}

constexpr const char* CASC_FILEPATHS[] = {
  "HD2\\anim\\main_%03d.anim",
  "anim\\main_%03d.anim"
};

const std::string OUTPUT_PATHS[] = {
  "graphics/low",
  "graphics/hd"
};

void convert_graphic(Casc& casc, const imagedat_info_t& img_def, bool use_hires) {
  std::vector<std::uint8_t> buffer;
  std::array<char, 64> filename;

  std::snprintf(filename.data(), filename.size(), CASC_FILEPATHS[use_hires], img_def.id);
  if (casc.read_file(filename.data(), buffer)) {
    convert_anim(buffer, img_def, OUTPUT_PATHS[use_hires], !use_hires);
  }
}

void convert_graphics(Casc& casc, bool use_hires) {
  ProgressBar progress(use_hires ? "Hi-Res Graphics" : "Lo-Res Graphics", unsigned(image_predefs.size()));
  Stopwatch stopwatch = Stopwatch::create();

  // Prep warp texture for Protoss structures
  convert_graphic(casc, WARP_TEXTURE, use_hires);

  size_t range_size = image_predefs.size() / std::thread::hardware_concurrency();
  std::vector<std::vector<imagedat_info_t>> data;
  for (size_t i = 0; i < image_predefs.size(); i += range_size) {
    auto target = image_predefs.begin() + i;
    data.emplace_back(target, target + std::min(range_size, image_predefs.size() - i));
  }

  std::for_each(std::execution::par_unseq, data.cbegin(), data.cend(), [&](const std::vector<imagedat_info_t>& img_defs) {
    for (const imagedat_info_t& img_def : img_defs) {
      convert_graphic(casc, img_def, use_hires);
      progress.inc_show_progress();
    }
  });

  stopwatch.stop();
  std::cerr << "\nCompleted in " << stopwatch.milliseconds() << "ms" << std::endl;
}

void extract_sounds(Casc& casc) {
  ProgressBar progress("Sounds", unsigned(sound_predefs.size()));
  Stopwatch stopwatch = Stopwatch::create();

  for (const std::string& snd_def : sound_predefs) {
    std::vector<std::uint8_t> buffer;
    if (casc.read_file(snd_def, buffer)) {
      std::string snd_path = snd_def;
      std::ranges::replace(snd_path, '\\', '/');
      std::filesystem::create_directories(std::filesystem::path(snd_path).parent_path());

      std::ofstream out(snd_path, std::ios::out | std::ios::binary);
      if (!out.write(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::cerr << "Failed to write " << snd_def << std::endl;
      }
    }
    else {
      std::cerr << "Failed to load " << snd_def << std::endl;
    }
    progress.inc_show_progress();
  }

  stopwatch.stop();
  std::cerr << "\nCompleted in " << stopwatch.milliseconds() << "ms" << std::endl;
}

void rip_creep_tiles(Casc& casc, bool use_hires) {
  const char* filepath = use_hires ? "TileSet\\AshWorld.dds.vr4" : "HD2\\TileSet\\AshWorld.dds.vr4";
  const std::string outputpath = use_hires ? "graphics/tiles/hd" : "graphics/tiles/low";

  std::vector<std::uint8_t> buffer;
  if (casc.read_file(filepath, buffer)) {
    convert_vr4_tiles(buffer, outputpath);
  }
  else {
    std::cerr << "Failed to load " << filepath << std::endl;
  }
}

void rip_icons(Casc& casc) {
  const char* filepath = "game\\icons.dds.grp";
  const std::string outputpath = "graphics/icons";

  std::vector<std::uint8_t> buffer;
  if (casc.read_file(filepath, buffer)) {
    convert_icons(buffer, outputpath);
  }
  else {
    std::cerr << "Failed to load " << filepath << std::endl;
  }
}

void rip_cmdicons(Casc& casc) {
  const char* filepath = "unit\\cmdicons\\cmdicons.dds.grp";
  const std::string outputpath = "graphics/cmdicons";

  std::vector<std::uint8_t> buffer;
  if (casc.read_file(filepath, buffer)) {
    convert_cmdicons(buffer, outputpath);
  }
  else {
    std::cerr << "Failed to load " << filepath << std::endl;
  }
}

void extract_tiles(Casc& casc) {
  ProgressBar progress("Tiles and Icons", 4);
  Stopwatch stopwatch = Stopwatch::create();

  rip_creep_tiles(casc, false);
  progress.inc_show_progress();

  rip_creep_tiles(casc, true);
  progress.inc_show_progress();

  rip_icons(casc);
  progress.inc_show_progress();

  rip_cmdicons(casc);
  progress.inc_show_progress();

  stopwatch.stop();
  std::cerr << "\nCompleted in " << stopwatch.milliseconds() << "ms" << std::endl;
}

int main(int argc, const char** argv) {
  if (argc < 2) {
    std::cerr << "Requires an argument - StarCraft: Remastered installation directory." << std::endl;
    return 1;
  }

//#ifdef _DEBUG
  std::cerr << "Attach debugger then press enter..." << std::endl;
  std::cin.ignore();
//#endif

  // Ensure fpng is fast
  fpng::fpng_init();

  // Shuffle the images to distribute the workload more evenly among threads
  std::random_device rd;
  std::mt19937 gen{ rd() };
  std::ranges::shuffle(image_predefs, gen);

  // Read the casc archive
  Casc casc(argv[1]);
  if (!casc.is_open()) return 2;

  // Convert to Factorio
  create_output_dirs();
  extract_tiles(casc);
  convert_graphics(casc, false);
  convert_graphics(casc, true);
  extract_sounds(casc);

  return 0;
}
