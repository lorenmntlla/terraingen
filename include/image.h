#pragma once
#include "color.h"
#include "dimension.h"
#include <string>

class Image {
  dimension_t m_length;
  dimension_t m_height;

  Color *m_pixels;

public:
  Image(dimension_t length = 0, dimension_t height = 0);

  Image(const Image &other);

  ~Image();

  Color &operator()(dimension_t x, dimension_t y) const;

  Color &operator()(dimension_t x, dimension_t y);

  bool savePPM(const std::string &fileName) const;

  bool readPPM(const std::string &fileName);

  dimension_t length() const;

  dimension_t height() const;

  Color *data() const;
};
