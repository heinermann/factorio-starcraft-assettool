#pragma once

#include <string>
#include <vector>
#include <mutex>

class Casc {
public:
  Casc();
  Casc(const std::string& casc_dir);

  ~Casc();

  Casc& operator=(const Casc& other) = delete;
  Casc& operator=(Casc&& other) = delete;

  bool open(const std::string& casc_dir);
  bool read_file(const std::string& file_name, std::vector<std::uint8_t>& result);
  bool close();

  bool is_open();

private:
  void* hCasc = nullptr;
  std::mutex casc_access_mutex = {};
};
