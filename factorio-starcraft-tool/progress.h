#pragma once

#include <mutex>
#include <iostream>

class ProgressBar {
public:
  ProgressBar() = delete;
  ProgressBar(const std::string& name, unsigned max_value, char fill_chr = '|', unsigned width = 100);

  void increment_progress();
  void inc_show_progress();
  void display(std::ostream& ostream);

private:
  std::string name;
  unsigned current_value = 0;
  unsigned max_value;
  unsigned width;
  char fill_chr;

  std::mutex progress_mutex = {};
};

