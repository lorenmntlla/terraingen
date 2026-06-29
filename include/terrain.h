#pragma once
#include "dimension.h"
#include <cstdint>
#include <string>

using altitude_t = int8_t;

class Terrain {
  dimension_t m_side;

  double m_rugosity;
  altitude_t m_maxHeight;
  altitude_t m_range;

  altitude_t *m_heightmap;

  altitude_t noise() const;
  void diamond(dimension_t bound);
  void square(dimension_t bound);

public:
  Terrain(dimension_t expoent = 1);

  Terrain(const Terrain &other);

  ~Terrain();

  altitude_t &operator()(dimension_t x, dimension_t y) const;

  altitude_t &operator()(dimension_t x, dimension_t y);

  bool saveFile(const std::string &fileName) const;

  bool readFile(const std::string &fileName);

  bool generate(double rugosity);

  dimension_t side() const;

  dimension_t lines() const;

  dimension_t columns() const;

  altitude_t *data();
};
