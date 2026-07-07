#pragma once
#include <cstdint>

using channel_t = uint8_t;

struct Color {
  channel_t r;
  channel_t g;
  channel_t b;

  template <typename T> Color operator*(T a) {
    return {channel_t(r * a), channel_t(g * a), channel_t(b * a)};
  }
};
