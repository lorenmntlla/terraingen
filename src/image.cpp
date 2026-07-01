#include "../include/image.h"
#include "../include/parseNumber.h"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

Image::Image(dimension_t length, dimension_t height)
    : m_length{length}, m_height{height},
      m_pixels{(length > 0 and height > 0) ? new Color[m_length * m_height]()
                                           : nullptr} {}
Image::Image(const Image &other)
    : m_length{other.m_length}, m_height{other.m_height},
      m_pixels{new Color[m_length * m_height]} {
  memcpy(m_pixels, other.m_pixels, m_length * m_height * sizeof(Color));
}

Image::~Image() {
  delete[] m_pixels;
  m_pixels = nullptr;
}

Color &Image::operator()(dimension_t x, dimension_t y) const {
  return m_pixels[y * m_length + x];
}

Color &Image::operator()(dimension_t x, dimension_t y) {
  return m_pixels[y * m_length + x];
}

void swap(Image &first, Image &second) {
  using std::swap;

  swap(first.m_length, second.m_length);
  swap(first.m_height, second.m_height);
  swap(first.m_pixels, second.m_pixels);
}

Image &Image::operator=(Image other) {
  swap(*this, other);
  return *this;
}

bool Image::savePPM(const std::string &fileName) const {
  std::ofstream PPM{fileName, std::ios::trunc | std::ios::out};

  if (!PPM) {
    auto err{errno};
    std::cerr << "Could not open " << fileName;

    if (err != 0)
      std::cerr << ": " << std::generic_category().message(err);

    std::cerr << '\n';
    return false;
  }

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

bool Image::readPPM(const std::string &fileName) {
  std::ifstream PPM{fileName};

  if (!PPM) {
    auto err{errno};
    std::cerr << "Could not open " << fileName;

    if (err != 0)
      std::cerr << ": " << std::generic_category().message(err);

    std::cerr << '\n';
    return false;
  }

  std::string current{};

  PPM >> current;

  if (current != "P3") {
    std::cerr << fileName << ": " << "Unsupported file format: " << current
              << '\n';

    return false;
  }

  PPM >> current;
  m_length = parseNumber<dimension_t>(current);

  PPM >> current;
  m_height = parseNumber<dimension_t>(current);

  PPM >> current;

  if (current != "255") {
    std::cerr << fileName << ": " << "Unsupported color range: " << current
              << '\n';

    return false;
  }

  delete[] m_pixels;
  m_pixels = new Color[m_length * m_height]();

  const dimension_t pixelTotal{m_length * m_height};
  for (dimension_t p{0}; p < pixelTotal; p++) {
    std::string red, green, blue;

    PPM >> red >> green >> blue;

    const channel_t r = parseNumber<channel_t>(red);
    const channel_t g = parseNumber<channel_t>(green);
    const channel_t b = parseNumber<channel_t>(blue);

    m_pixels[p] = {r, g, b};
  }

  return true;
}

dimension_t Image::length() const { return m_length; }

dimension_t Image::height() const { return m_height; }

Color *Image::data() const { return m_pixels; }
