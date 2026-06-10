#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
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

  void addColor(const Color &color) { m_colors.push_back(color); }

  void addColor(const std::uint8_t &r, const uint8_t &g, const uint8_t &b) {
    m_colors.push_back(Color{r, g, b});
  }

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

  size_t getColorQuantity() const { return m_colors.size(); }

  std::optional<Color> getColor(size_t i = 0) const {
    if (i >= getColorQuantity())
      return std::nullopt;

    return m_colors[i];
  }

  bool printColor(size_t i = 0) const {
    auto maybe_color{getColor(i)};
    if (!maybe_color) {
      std::cerr << "Color " << i << " not in palette\n";
      return false;
    }

    Color color = *maybe_color;

    std::cout << '(' << (int)color.r << ", " << (int)color.g << ", "
              << (int)color.b << ')' << '\n';

    return true;
  }

  void printAllColors() const {
    for (size_t i{0}; i < getColorQuantity(); i++)
      printColor(i);
  }
};
