#pragma once
#include "color.h"
#include "palette.h"
#include <fstream>
#include <string>
#include <vector>

typedef long unsigned int dimension_t;

class Image {
  dimension_t m_length;
  dimension_t m_height;

  Color *m_pixels;

public:
  Image(dimension_t length, dimension_t height);

  Image(const std::string &fileName);

  Color &operator()(dimension_t x, dimension_t y) const;

  dimension_t length() const;

  dimension_t height() const;

  Color *data() const;

  Color getPixel(dimension_t x, dimension_t y) const;

  bool savePPM(const std::string &fileName) const;

  Color &operator()(dimension_t x, dimension_t y);

  void setPixel(dimension_t x, dimension_t y, const Color &color);

  ~Image();
};
