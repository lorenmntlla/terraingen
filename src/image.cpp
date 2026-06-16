#include "../include/image.h"
#include <charconv>
#include <fstream>
#include <string>
#include <string_view>

dimension_t Image::parseNumber(std::string_view sv) const {
  dimension_t decimal{};
  std::from_chars(sv.data(), sv.data() + sv.size(), decimal);

  return decimal;
}

Image::Image(dimension_t length, dimension_t height)
    : m_length{length}, m_height{height},
      m_pixels{(length > 0 and height > 0) ? new Color[m_length * m_height]()
                                           : nullptr} {}

Color &Image::operator()(dimension_t x, dimension_t y) const {
  return m_pixels[y * m_length + x];
}

Color Image::getPixel(dimension_t x, dimension_t y) const {
  return m_pixels[y * m_length + x];
}

dimension_t Image::length() const { return m_length; }

dimension_t Image::height() const { return m_height; }

Color *Image::data() const { return m_pixels; }

bool Image::savePPM(const std::string &fileName) const {
  std::ofstream PPM{fileName, std::ios::trunc | std::ios::out};

  PPM << "P3\n";
  PPM << m_length << ' ' << m_height << '\n';
  PPM << 255 << '\n';

  const dimension_t pixelTotal{m_length * m_height};

  for (dimension_t pixel{0}; pixel < pixelTotal; pixel++) {
    const auto [red, green, blue] = m_pixels[pixel];

    PPM << (int)red << ' ' << (int)green << ' ' << (int)blue << ' ';
  }

  return true;
}

Color &Image::operator()(dimension_t x, dimension_t y) {
  return m_pixels[y * m_length + x];
}

bool Image::readPPM(const std::string &fileName) {
  std::ifstream PPM{fileName};

  if (!PPM)
    throw std::system_error(errno, std::generic_category(), fileName);

  std::string current;

  PPM >> current;
  if (current != "P3")
    return false;

  PPM >> current;
  m_length = parseNumber(current);

  PPM >> current;
  m_height = parseNumber(current);

  PPM >> current;
  if (current != "255")
    return false;

  delete[] m_pixels;
  m_pixels = new Color[m_length * m_height]();

  const dimension_t pixelTotal{m_length * m_height};
  for (dimension_t p{0}; p < pixelTotal; p++) {
    std::string red, green, blue;

    PPM >> red >> green >> blue;

    channel_t r = (channel_t)parseNumber(red);
    channel_t g = (channel_t)parseNumber(green);
    channel_t b = (channel_t)parseNumber(blue);

    m_pixels[p] = {r, g, b};
  }

  return true;
}

void Image::setPixel(dimension_t x, dimension_t y, const Color &color) {
  m_pixels[y * m_length + x] = color;
}

Image::~Image() {
  delete[] m_pixels;
  m_pixels = nullptr;
}
