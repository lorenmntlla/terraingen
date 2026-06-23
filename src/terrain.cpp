#include "../include/terrain.h"
#include <stdexcept>
#include <string>

bool Terrain::isPowOfTwo(dimension_t a) { return ((a & (a - 1)) == 0); }

Terrain::Terrain(dimension_t side)
    : m_side{(side > 1 and isPowOfTwo(side - 1)) ? side : 0}, m_rugosity{},
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

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) {
  return m_heightmap[y * m_side + x];
}

Terrain::~Terrain() {
  delete[] m_heightmap;
  m_heightmap = nullptr;
}
