#pragma once
#include "dimension.h"
#include <cstdint>
#include <string>

using altitude_t = int8_t;

class Terrain {
  dimension_t m_side;

  unsigned long m_seed;
  bool m_isSeeded;

  altitude_t m_maxHeight;
  altitude_t m_range;

  altitude_t *m_heightmap;

  altitude_t noise() const;
  void diamond(dimension_t bound);
  void square(dimension_t bound);

public:
  Terrain(dimension_t expoent = 1);

  Terrain(const Terrain &other);

  Terrain(Terrain &&other) noexcept;

  ~Terrain();

  altitude_t &operator()(dimension_t x, dimension_t y) const;

  altitude_t &operator()(dimension_t x, dimension_t y);

  Terrain &operator=(Terrain other) noexcept;

  bool saveFile(const std::string &fileName) const;

  bool readFile(const std::string &fileName);

  unsigned long getSeed() const;

  void setSeed(unsigned long seed);

  void generate(double rugosity);

  dimension_t side() const;

  dimension_t lines() const;

  dimension_t columns() const;

  altitude_t *data();

  friend void swap(Terrain &first, Terrain &second) noexcept;
};
