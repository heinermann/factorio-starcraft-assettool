#include "casc.h"

#include <CascLib.h>

Casc::Casc() {}

Casc::Casc(const std::string& casc_dir) {
  open(casc_dir);
}

Casc::~Casc() {
  close();
}

bool Casc::open(const std::string& casc_dir) {
  return CascOpenStorage(casc_dir.c_str(), 0, &hCasc);
}

bool Casc::read_file(const std::string& file_name, std::vector<std::uint8_t>& result) {
  std::lock_guard guard(casc_access_mutex);

  /* TODO: exceptions
  auto raise_error = [&](const std::string& msg) {
    std::cerr << "Failed to open file in Casc archive: " << msg << "\n";
    std::cerr << "\tFile: " << file_name << "\n";
    std::cerr << "\tError: " << GetCascError() << std::endl;
  };
  */

  HANDLE hFile = nullptr;
  if (!CascOpenFile(hCasc, file_name.c_str(), 0, 0, &hFile)) {
    //raise_error("CascOpenFile");
    return false;
  }

  DWORD filesize = CascGetFileSize(hFile, nullptr);
  if (filesize == CASC_INVALID_SIZE) {
    //raise_error("CascGetFileSize");
    return false;
  }

  result.resize(filesize);
  DWORD read_size = 0;
  if (!CascReadFile(hFile, result.data(), filesize, &read_size) || read_size != filesize) {
    //raise_error("CascReadFile");
    return false;
  }

  return CascCloseFile(hFile);
}

bool Casc::close() {
  bool result = CascCloseStorage(hCasc);
  hCasc = nullptr;
  return result;
}

bool Casc::is_open() {
  return hCasc != nullptr;
}
