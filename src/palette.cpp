#include "../include/palette.h"
#include <charconv>
#include <iostream>

Palette::Palette() : m_colors{} {}

Palette::Palette(std::ifstream &file) : m_colors{} {
  std::string hex{};

  while (std::getline(file, hex))
    addColor(hex);
}

uint8_t Palette::parseChannel(std::string_view sv) const {
  uint8_t channel{};
  std::from_chars(sv.data(), sv.data() + sv.size(), channel, 16);

  return channel;
}

Palette::Palette(const Palette &palette) : m_colors{palette.m_colors} {}

Palette::Palette(const std::vector<Color> &colors) : m_colors{colors} {}

void Palette::addColor(const Color &color) { m_colors.push_back(color); }

void Palette::addColor(const uint8_t &r, const uint8_t &g, const uint8_t &b) {
  m_colors.push_back(Color{r, g, b});
}

void Palette::addColor(std::string_view hex) {
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

size_t Palette::getColorQuantity() const { return m_colors.size(); }

std::optional<Color> Palette::getColor(size_t i) const {
  if (i >= getColorQuantity())
    return std::nullopt;

  return m_colors[i];
}

bool Palette::printColor(size_t i) const {
  std::optional<Color> maybe_color{Palette::getColor(i)};
  if (!maybe_color) {
    std::cerr << "Color " << i << " not in palette\n";
    return false;
  }

  Color color = *maybe_color;

  std::cout << '(' << (int)color.r << ", " << (int)color.g << ", "
            << (int)color.b << ')' << '\n';

  return true;
}

void Palette::printAllColors() const {
  for (size_t i{0}; i < Palette::getColorQuantity(); i++)
    printColor(i);
}
