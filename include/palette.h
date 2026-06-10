#pragma once
#include <charconv>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class Palette {
  std::vector<Color> m_colors{};

  uint8_t parseChannel(std::string_view sv) {
    uint8_t channel{};
    std::from_chars(sv.data(), sv.data() + sv.size(), channel, 16);

    return channel;
  }

public:
  Palette() : m_colors{} {}

  Palette(std::ifstream &file) : m_colors{} {
    std::string color_hex{};

    while (std::getline(file, color_hex))
      addColor(color_hex);
  }

  Palette(const Palette &palette) : m_colors{palette.m_colors} {}

  void addColor(const Color &color) { m_colors.push_back(color); }

  void addColor(const uint8_t &r, const uint8_t &g, const uint8_t &b) {
    m_colors.push_back(Color{r, g, b});
  }

  void addColor(std::string_view hex) {
    if (hex.empty())
      return;

    if (hex.front() == '#')
      hex.remove_prefix(1);

    // TODO: throw exception instead of silently failing
    if (hex.size() != 6)
      return;

    uint8_t red = parseChannel(hex.substr(0, 2));
    uint8_t green = parseChannel(hex.substr(2, 2));
    uint8_t blue = parseChannel(hex.substr(4, 2));

    m_colors.push_back(Color{red, green, blue});
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
