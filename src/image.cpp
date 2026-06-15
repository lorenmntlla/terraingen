#include "../include/image.h"
#include <fstream>
#include <string>

Image::Image(dimension_t length, dimension_t height)
    : m_length{length}, m_height{height}, m_pixels{nullptr} {
  m_pixels = new Color[m_length * m_height]{Color{0, 0, 0}};
}

Color Image::getPixel(dimension_t x, dimension_t y) const {
  return m_pixels[y * m_length + x];
}

dimension_t Image::length() const { return m_length; }

dimension_t Image::height() const { return m_height; }

Color *Image::data() const { return m_pixels; }

void Image::savePPM(const std::string &fileName) const {
  if (m_pixels == nullptr)
    return;

  std::ofstream PPM{fileName};

  PPM << "P3\n";
  PPM << m_length << ' ' << m_height << '\n';
  PPM << 255 << '\n';

  size_t pixelTotal{m_length * m_height};

  for (size_t pixel{0}; pixel < pixelTotal; pixel++) {
    const auto [red, green, blue] = m_pixels[pixel];

    PPM << (int)red << ' ' << (int)green << ' ' << (int)blue << ' ';
  }

  PPM.close();
}

void Image::setPixel(dimension_t x, dimension_t y, const Color &color) {
  m_pixels[y * m_length + x] = color;
}

Image::~Image() {
  delete m_pixels;
  m_pixels = nullptr;
}
