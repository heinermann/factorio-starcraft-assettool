#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <execution>

#include "casc.h"

#include "convert_anim.h"
#include "image_predefs.h"

void create_output_dirs() {
  constexpr const char* const out_dirs[] = {
    "graphics",
    "sound",
    "locale"
  };

  for (auto dir : out_dirs) {
    std::filesystem::create_directory(dir);
  }
}

void convert_graphics(Casc& casc) {
  auto clock_start = std::chrono::steady_clock::now();

  std::cerr << "Converting Graphics\n";

  std::for_each(std::execution::par_unseq, image_predefs.cbegin(), image_predefs.cend(), [&casc](const imagedat_info_t& img_def) {
    std::cerr << img_def.id << ", ";  // TODO: rid this

    std::vector<std::uint8_t> buffer;
    std::array<char, 64> filename;

    std::snprintf(filename.data(), filename.size(), "anim\\main_%03d.anim", img_def.id);
    if (casc.read_file(filename.data(), buffer)) {
      convert_anim(buffer, img_def);
    }
  });

  auto clock_end = std::chrono::steady_clock::now();
  std::cerr << "Done. Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock_end - clock_start).count() << "ms" << std::endl;
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
  convert_graphics(casc);

  return 0;
}
