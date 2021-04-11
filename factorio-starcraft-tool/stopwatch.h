#pragma once

#include <chrono>

class Stopwatch {
public:
  void start();
  void stop();
  void reset();

  long long milliseconds();

  static Stopwatch create();
private:
  std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::time_point::min();
  std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::time_point::min();
};
