#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
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

  Palette(std::ifstream &file) : m_colors{} {
    std::string color_hex{};

    while (std::getline(file, color_hex))
      addColor(color_hex);
  }

  Palette(const Palette &palette) : m_colors{palette.m_colors} {}

  void addColor(const std::uint8_t &r, const uint8_t &g, const uint8_t &b) {
    m_colors.push_back({r, g, b});
  }

  void addColor(const Color &color) { m_colors.push_back(color); }

  void addColor(std::string_view color_hex) {
    Color color{};
    for (size_t i{0}; i < color_hex.size() - 1; i += 2) {
      if (color_hex[i] == '#')
        i++;

      std::string color_digit{color_hex[i], color_hex[i + 1]};

      if (i == 0 or i == 1)
        color.r = static_cast<std::uint8_t>(std::stoi(color_digit, 0, 16));

      if (i == 2 or i == 3)
        color.g = static_cast<std::uint8_t>(std::stoi(color_digit, 0, 16));

      if (i == 4 or i == 5)
        color.b = static_cast<std::uint8_t>(std::stoi(color_digit, 0, 16));
    }

    m_colors.push_back(color);
  }

  size_t getColorQuantity() { return m_colors.size(); }

  void printColor(size_t i = 0) {
    std::cout << '(' << (int)m_colors[i].r << ", " << (int)m_colors[i].g << ", "
              << (int)m_colors[i].b << ')' << '\n';
  }

  void printAllColors() {
    for (size_t i{0}; i < getColorQuantity(); i++)
      printColor(i);
  }
};
