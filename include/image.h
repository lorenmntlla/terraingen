#include "color.h"
#include "palette.h"
#include <fstream>
#include <vector>

typedef unsigned int dimension_t;

class Image {
  dimension_t m_length;
  dimension_t m_height;

  Color *m_pixels;

public:
  Image(dimension_t length, dimension_t height);

  Image(std::ifstream &file);

  Color getPixel(dimension_t x, dimension_t y) const;

  void savePPM(const std::string &fileName) const;

  void setPixel(dimension_t x, dimension_t y, const Color &color);

  ~Image();
};
