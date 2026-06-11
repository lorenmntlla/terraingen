#include "../include/image.h"

Image::Image(dimension_t length, dimension_t height)
    : m_length{length}, m_height{height}, m_pixels{nullptr} {
  m_pixels = new Color[m_length * m_height]{Color{0, 0, 0}};
}

Color Image::getPixel(dimension_t x, dimension_t y) const {
  return m_pixels[y * m_height + x];
}

void Image::setPixel(dimension_t x, dimension_t y, const Color &color) {
  m_pixels[y * m_height + x] = color;
}

Image::~Image() {
  delete m_pixels;
  m_pixels = nullptr;
}
