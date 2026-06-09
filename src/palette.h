#pragma once
#include <vector>

struct Color {
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
};

class Palette {
  std::vector<Color> m_colors{};

public:
  Palette() : m_colors{} {}

};
