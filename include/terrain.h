#pragma once
#include "dimension.h"
#include <random>
#include <string>

typedef int8_t altitude_t;

class Terrain {
  const dimension_t m_side;

  double m_rugosity;
  altitude_t m_range;

  std::mt19937 m_generator;

  altitude_t *m_heightmap;

  bool isPowOfTwo(dimension_t a) const;

  altitude_t random();
  void diamond(dimension_t boundary, dimension_t dx = 0, dimension_t dy = 0);
  void square(dimension_t boundary, dimension_t dx = 0, dimension_t dy = 0);

public:
  Terrain(dimension_t side = 3);

  dimension_t side() const;

  dimension_t lines() const;

  dimension_t columns() const;

  altitude_t &operator()(dimension_t x, dimension_t y) const;

  bool saveFile(const std::string &fileName) const;

  bool generate(double rugosity);

  altitude_t &operator()(dimension_t x, dimension_t y);

  altitude_t *data();

  bool readFile(const std::string &fileName);

  ~Terrain();
};
