#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <execution>

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

void convert_graphics(Casc& casc, bool use_hires) {
  ProgressBar progress(use_hires ? "Hi-Res Graphics" : "Lo-Res Graphics", unsigned(image_predefs.size()));
  Stopwatch stopwatch = Stopwatch::create();

  const char* filepath = use_hires ? "anim\\main_%03d.anim" : "HD2\\anim\\main_%03d.anim";
  const std::string outputpath = use_hires ? "graphics/hd" : "graphics/low";
  std::for_each(std::execution::par_unseq, image_predefs.cbegin(), image_predefs.cend(), [&](const imagedat_info_t& img_def) {
    std::vector<std::uint8_t> buffer;
    std::array<char, 64> filename;

    std::snprintf(filename.data(), filename.size(), filepath, img_def.id);
    if (casc.read_file(filename.data(), buffer)) {
      convert_anim(buffer, img_def, outputpath, !use_hires);
    }
    progress.inc_show_progress();
  });

  stopwatch.stop();
  std::cerr << "\nCompleted in " << stopwatch.milliseconds() << "ms" << std::endl;
}

void extract_sounds(Casc& casc) {
  ProgressBar progress("Sounds", unsigned(sound_predefs.size()));
  Stopwatch stopwatch = Stopwatch::create();

  std::for_each(std::execution::par_unseq, sound_predefs.cbegin(), sound_predefs.cend(), [&](const std::string& snd_def) {
    std::vector<std::uint8_t> buffer;
    if (casc.read_file(snd_def, buffer)) {
      std::filesystem::create_directories(std::filesystem::path(snd_def).parent_path());

      std::ofstream out(snd_def, std::ios::out | std::ios::binary);
      if (!out.write(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::cerr << "Failed to write " << snd_def << std::endl;
      }
    }
    else {
      std::cerr << "Failed to load " << snd_def << std::endl;
    }
    progress.inc_show_progress();
  });

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

  Casc casc(argv[1]);
  if (!casc.is_open()) return 2;

  create_output_dirs();
  extract_tiles(casc);
  convert_graphics(casc, false);
  convert_graphics(casc, true);
  extract_sounds(casc);

  return 0;
}
