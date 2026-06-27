#pragma once
#include <cstdint>

using channel_t = uint8_t;

struct Color {
  channel_t r;
  channel_t g;
  channel_t b;
};
