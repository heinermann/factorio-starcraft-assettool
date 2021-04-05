#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <CascLib.h>

#include "convert.h"
#include "image_predefs.h"

HANDLE open_casc_storage(const std::string& install_dir) {
  HANDLE hCasc = nullptr;
  if (!CascOpenStorage(install_dir.c_str(), 0, &hCasc)) {
    std::cerr << "Failed to open Casc archive, are you sure you chose the correct directory?" << std::endl;
    return nullptr;
  }
  return hCasc;
}

bool get_file_data(HANDLE hCasc, const std::string& file_name, std::vector<std::uint8_t>& result) {

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

int main(int argc, const char** argv) {
  if (argc < 2) {
    std::cerr << "Requires an argument - StarCraft: Remastered installation directory." << std::endl;
    return 1;
  }
  
  HANDLE hCasc = open_casc_storage(argv[1]);
  if (hCasc == nullptr) return 2;

  std::vector<std::uint8_t> test;
  get_file_data(hCasc, "anim\\main_000.anim", test);
  
  std::ofstream of("main_000.anim", std::ios::binary);
  of.write(reinterpret_cast<const char*>(test.data()), test.size());

  convert_anim(test, image_predefs[0]);
}
