#include "color.h"
#include "palette.h"
#include <fstream>
#include <vector>

typedef unsigned int dimension_t;

class Image {
  dimension_t m_length;
  dimension_t m_height;

  std::vector<std::vector<Color>> m_pixels;

public:
  Image(dimension_t length, dimension_t height);

  Image(std::ifstream &file);

  Color getPixel(dimension_t line, dimension_t column);

  void savePPM(std::string file);

  ~Image();
};
