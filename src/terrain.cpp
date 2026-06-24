#include "../include/terrain.h"
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>

altitude_t *Terrain::data() { return m_heightmap; }

bool Terrain::isPowOfTwo(dimension_t a) const { return ((a & (a - 1)) == 0); }

altitude_t Terrain::random() {
  std::uniform_int_distribution<altitude_t> dist{(int8_t)-m_range, m_range};

  return dist(m_generator);
}

void Terrain::diamond(dimension_t boundary, dimension_t dx, dimension_t dy) {
  const altitude_t upperLeft{operator()(dx, dy)};
  const altitude_t upperRight{operator()(dx, boundary + dy)};
  const altitude_t bottomLeft{operator()(boundary + dx, dy)};
  const altitude_t bottomRight{operator()(boundary + dx, boundary + dy)};

  altitude_t *center{&operator()((boundary / 2) + dx, (boundary / 2) + dy)};

  *center = (upperLeft + upperRight + bottomLeft + bottomRight) / 4 + random();

  square(boundary, dx, dy);
}

void Terrain::square(dimension_t boundary, dimension_t dx, dimension_t dy) {
  const altitude_t upperLeft{operator()(dx, dy)};
  const altitude_t upperRight{operator()(dx, boundary + dy)};
  const altitude_t bottomLeft{operator()(boundary + dx, dy)};
  const altitude_t bottomRight{operator()(boundary + dx, boundary + dy)};
  const altitude_t center{operator()((boundary / 2) + dx, (boundary / 2) + dy)};

  altitude_t *left{&operator()(dx, (boundary / 2) + dy)};
  altitude_t *top{&operator()((boundary / 2) + dx, dy)};
  altitude_t *right{&operator()(boundary + dx, (boundary / 2) + dy)};
  altitude_t *bottom{&operator()((boundary / 2) + dx, boundary + dy)};

  // TODO: Consider square point out of border
  *left = (upperLeft + bottomLeft + center) / 3 + random();
  *top = (upperLeft + upperRight + center) / 3 + random();
  *right = (upperRight + bottomRight + center) / 3 + random();
  *bottom = (bottomLeft + bottomRight + center) / 3 + random();

  m_range = (altitude_t)(m_range * std::pow(2, -m_rugosity));

  if (boundary > 1) {
    diamond(boundary - 2, dx, dy);
    diamond(boundary - 2, dx + 2, dy);
    diamond(boundary - 2, dx, dy + 2);
    diamond(boundary - 2, dx + 2, dy + 2);
  }
}

Terrain::Terrain(dimension_t side)
    : m_side{(side > 1 and isPowOfTwo(side - 1)) ? side : 0}, m_rugosity{},
      m_range{INT8_MAX}, m_generator{std::mt19937{std::random_device{}()}},
      m_heightmap{(m_side == 0) ? nullptr : new altitude_t[m_side * m_side]()} {
  if (m_side == 0)
    throw std::invalid_argument(
        "Terrain dimension must be (2^n) + 1. Received: " +
        std::to_string(side));
}

dimension_t Terrain::side() const { return m_side; }
dimension_t Terrain::lines() const { return m_side; }
dimension_t Terrain::columns() const { return m_side; }

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) const {
  return m_heightmap[y * m_side + x];
}

bool Terrain::generate(double rugosity) {
  m_rugosity = rugosity;

  const dimension_t boundary{m_side - 1};

  operator()(0, 0) = random();
  operator()(0, boundary) = random();
  operator()(boundary, 0) = random();
  operator()(boundary, boundary) = random();

  diamond(boundary);

  return true;
}

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) {
  return m_heightmap[y * m_side + x];
}

Terrain::~Terrain() {
  delete[] m_heightmap;
  m_heightmap = nullptr;
}
