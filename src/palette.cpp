#include "../include/palette.h"
#include <charconv>
#include <fstream>
#include <string>
#include <string_view>

Palette::Palette() : m_colors{} {}

Palette::Palette(const std::string &fileName) : m_colors{} {
  std::ifstream file{fileName};

  std::string hex{};

  while (std::getline(file, hex)) {
    for (size_t pos{hex.find('#')}; pos != std::string::npos;
         pos = hex.find('#', pos + 1))
      addColor(hex.substr(pos + 1, 6));
  }

  file.close();
}

channel_t Palette::parseChannel(std::string_view sv) const {
  channel_t channel{};
  std::from_chars(sv.data(), sv.data() + sv.size(), channel, 16);

  return channel;
}

Palette::Palette(const Palette &palette) : m_colors{palette.m_colors} {}

Palette::Palette(const std::vector<Color> &colors) : m_colors{colors} {}

void Palette::addColor(const Color &color) { m_colors.push_back(color); }

void Palette::addColor(channel_t r, channel_t g, channel_t b) {
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

  channel_t red = parseChannel(hex.substr(0, 2));
  channel_t green = parseChannel(hex.substr(2, 2));
  channel_t blue = parseChannel(hex.substr(4, 2));

  m_colors.push_back(Color{red, green, blue});
}

size_t Palette::size() const { return m_colors.size(); }

std::optional<Color> Palette::getColor(size_t i) const {
  if (i >= size())
    return std::nullopt;

  return m_colors[i];
}
