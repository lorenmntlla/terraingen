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

  void addColor(const std::uint8_t &r, const uint8_t &g, const uint8_t &b) {
    m_colors.push_back({r, g, b});
  }

  void addColor(const Color &color) { m_colors.push_back(color); }
};
