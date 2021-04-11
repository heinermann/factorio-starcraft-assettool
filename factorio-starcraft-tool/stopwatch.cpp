#include "stopwatch.h"

void Stopwatch::start() {
  reset();
  start_time = std::chrono::steady_clock::now();
}

void Stopwatch::stop() {
  end_time = std::chrono::steady_clock::now();
}

void Stopwatch::reset() {
  start_time = std::chrono::steady_clock::time_point::min();
  end_time = std::chrono::steady_clock::time_point::min();
}

long long Stopwatch::milliseconds() {
  if (start_time == std::chrono::steady_clock::time_point::min() || end_time == std::chrono::steady_clock::time_point::min())
    return -1;

  return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
}

Stopwatch Stopwatch::create() {
  Stopwatch result;
  result.start();
  return result;
}
