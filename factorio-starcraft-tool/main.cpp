#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <execution>
#include <mutex>

#include <CascLib.h>

#include "convert_anim.h"
#include "image_predefs.h"

HANDLE open_casc_storage(const std::string& install_dir) {
  HANDLE hCasc = nullptr;
  if (!CascOpenStorage(install_dir.c_str(), 0, &hCasc)) {
    std::cerr << "Failed to open Casc archive, are you sure you chose the correct directory?" << std::endl;
    return nullptr;
  }
  return hCasc;
}

std::mutex g_casc_access_mutex;
bool get_file_data(HANDLE hCasc, const std::string& file_name, std::vector<std::uint8_t>& result) {
  std::lock_guard guard(g_casc_access_mutex);

  auto raise_error = [&](const std::string& msg) {
    std::cerr << "Failed to open file in Casc archive: " << msg << "\n";
    std::cerr << "\tFile: " << file_name << "\n";
    std::cerr << "\tError: " << GetCascError() << std::endl;
  };

  HANDLE hFile = nullptr;
  if (!CascOpenFile(hCasc, file_name.c_str(), 0, 0, &hFile)) {
    raise_error("CascOpenFile");
    return false;
  }

  DWORD filesize = CascGetFileSize(hFile, nullptr);
  if (filesize == CASC_INVALID_SIZE) {
    raise_error("CascGetFileSize");
    return false;
  }

  result.resize(filesize);
  DWORD read_size = 0;
  if (!CascReadFile(hFile, result.data(), filesize, &read_size) || read_size != filesize) {
    raise_error("CascReadFile");
    return false;
  }

  CascCloseFile(hFile);
  return true;
}

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

void convert_graphics(HANDLE hCasc) {
  auto clock_start = std::chrono::steady_clock::now();

  std::cerr << "Converting Graphics\n";

  std::for_each(std::execution::par_unseq, image_predefs.cbegin(), image_predefs.cend(), [&hCasc](const imagedat_info_t& img_def) {
    std::cerr << img_def.id << ", ";  // TODO: rid this

    std::vector<std::uint8_t> buffer;
    std::array<char, 64> filename;

    std::snprintf(filename.data(), filename.size(), "anim\\main_%03d.anim", img_def.id);
    if (get_file_data(hCasc, filename.data(), buffer)) {
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

  HANDLE hCasc = open_casc_storage(argv[1]);
  if (hCasc == nullptr) return 2;

  create_output_dirs();
  convert_graphics(hCasc);

  return 0;
}
