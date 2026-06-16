#pragma once
#include "color.h"
#include <string>
#include <string_view>

typedef long unsigned int dimension_t;

class Image {
  dimension_t m_length;
  dimension_t m_height;

  Color *m_pixels;

  dimension_t parseNumber(std::string_view sv) const;

public:
  Image(dimension_t length = 0, dimension_t height = 0);

  Image(const std::string &fileName);

  Color &operator()(dimension_t x, dimension_t y) const;

  dimension_t length() const;

  dimension_t height() const;

  Color *data() const;

  Color getPixel(dimension_t x, dimension_t y) const;

  bool savePPM(const std::string &fileName) const;

  Color &operator()(dimension_t x, dimension_t y);

  void setPixel(dimension_t x, dimension_t y, const Color &color);

  bool readPPM(const std::string &fileName);

  ~Image();
};
