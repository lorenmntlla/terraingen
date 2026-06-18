#pragma once
#include "dimension.h"
#include <cstdint>
#include <string>

typedef uint8_t altitude_t;

class Terrain {
  dimension_t m_side;
  float m_rugosity;

  altitude_t *m_terrain;

  bool isPowOfTwo(dimension_t a);

public:
  Terrain(dimension_t side = 3);

  dimension_t side() const;

  dimension_t lines() const;

  dimension_t columns() const;

  altitude_t &operator()(dimension_t x, dimension_t y) const;

  bool saveFile(const std::string &fileName) const;

  bool generate(dimension_t side, float rugosity);

  altitude_t &operator()(dimension_t x, dimension_t y);

  bool readFile(const std::string &fileName);

  ~Terrain();
};
