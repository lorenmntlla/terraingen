#pragma once
#include "color.h"
#include <fstream>
#include <optional>
#include <string_view>
#include <vector>

class Palette {
  std::vector<Color> m_colors{};

  uint8_t parseChannel(std::string_view sv) const;

public:
  Palette();

  Palette(std::ifstream &file);

  Palette(const Palette &palette);

  Palette(const std::vector<Color> &colors);

  void addColor(const Color &color);

  void addColor(const uint8_t &r, const uint8_t &g, const uint8_t &b);

  void addColor(std::string_view hex);

  size_t getColorQuantity() const;

  std::optional<Color> getColor(size_t i = 0) const;

  bool printColor(size_t i = 0) const;

  void printAllColors() const;
};
