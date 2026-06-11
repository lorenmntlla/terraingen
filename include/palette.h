#pragma once
#include "color.h"
#include <fstream>
#include <optional>
#include <string_view>
#include <vector>

class Palette {
  std::vector<Color> m_colors{};

  channel_t parseChannel(std::string_view sv) const;

public:
  Palette();

  Palette(const std::string &fileName);

  Palette(const Palette &palette);

  Palette(const std::vector<Color> &colors);

  void addColor(const Color &color);

  void addColor(channel_t r, channel_t g, channel_t b);

  void addColor(std::string_view hex);

  size_t getColorQuantity() const;

  std::optional<Color> getColor(size_t i = 0) const;

  bool printColor(size_t i = 0) const;

  void printAllColors() const;
};
