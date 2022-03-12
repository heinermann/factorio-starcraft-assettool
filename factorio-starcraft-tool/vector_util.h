#pragma once

#include <tuple>
#include <cstdint>
#include <cmath>

template <class T>
struct Vec3 {
  T x, y, z;

  Vec3<T> operator*(const Vec3<T>& other) const {
    auto [x1, y1, z1] = *this;
    auto [x2, y2, z2] = other;
    return { x1 * x2, y1 * y2, z1 * z2 };
  }

  T sum() const {
    auto [v1, v2, v3] = *this;
    return v1 + v2 + v3;
  }
};

// source: https://github.com/neivv/animosity/blob/master/src/normal_encoding.rs#L15
Vec3<double> decode_normal(std::uint8_t x_in, std::uint8_t y_in) {
  double x = x_in / 255.0 * 2 - 1;
  double y = y_in / 255.0 * 2 - 1;

  double xy_sq = x * x + y * y;
  if (xy_sq > 1) {
    double len = std::sqrt(xy_sq);
    return { x / len, y / len, 0 };
  }
  else {
    double z = std::sqrt(1 - xy_sq);
    return { x, y, z };
  }
}

