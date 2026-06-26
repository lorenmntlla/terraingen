#pragma once
#include "dimension.h"
#include <cstdint>
#include <string>

using altitude_t = int8_t;

class Terrain {
  const dimension_t m_side;

  double m_rugosity;
  altitude_t m_range;

  altitude_t *m_heightmap;

  altitude_t noise();
  void diamond(dimension_t bound);
  void square(dimension_t bound);

public:
  Terrain(dimension_t side);

  dimension_t side() const;

  dimension_t lines() const;

  dimension_t columns() const;

  altitude_t &operator()(dimension_t x, dimension_t y) const;

  bool saveFile(const std::string &fileName) const;

  bool generate(double rugosity);

  altitude_t &operator()(dimension_t x, dimension_t y);

  bool readFile(const std::string &fileName);

  altitude_t *data();

  ~Terrain();
};
