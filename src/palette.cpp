#include "../include/palette.h"
#include "../include/parseNumber.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

Palette::Palette() : m_colors{} {}

Palette::Palette(const std::string &fileName) : m_colors{} {
  std::ifstream file{fileName};

  if (!file)
    throw std::system_error(errno, std::generic_category(), fileName);

  std::string hex{};

  while (std::getline(file, hex)) {
    for (size_t pos{hex.find('#')}; pos != std::string::npos;
         pos = hex.find('#', pos + 1))
      addColor(hex.substr(pos + 1, 6));
  }
}

Palette::Palette(const Palette &palette) : m_colors{palette.m_colors} {}

Palette::Palette(const std::vector<Color> &colors) : m_colors{colors} {}

size_t Palette::size() const { return m_colors.size(); }

std::optional<Color> Palette::getColor(size_t i) const {
  if (i >= size())
    return std::nullopt;

  return m_colors[i];
}

void Palette::addColor(const Color &color) { m_colors.push_back(color); }

void Palette::addColor(channel_t r, channel_t g, channel_t b) {
  m_colors.push_back(Color{r, g, b});
}

void Palette::addColor(std::string_view hex) {
  if (hex.empty())
    throw std::invalid_argument("String is empty.");

  if (hex.front() == '#')
    hex.remove_prefix(1);

  if (hex.size() != 6)
    throw std::invalid_argument("Hexadecimal must have exactly 6 digits.");

  channel_t red = parseNumber<channel_t>(hex.substr(0, 2), 16);
  channel_t green = parseNumber<channel_t>(hex.substr(2, 2), 16);
  channel_t blue = parseNumber<channel_t>(hex.substr(4, 2), 16);

  m_colors.push_back(Color{red, green, blue});
}
