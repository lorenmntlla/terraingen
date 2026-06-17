#include "../include/terrain.h"
#include <stdexcept>

Terrain::Terrain(dimension_t side)
    : m_side{(side > 1 and side % 2 == 1) ? side : 0}, m_rugosity{},
      m_terrain{(m_side > 1 and m_side % 2 == 1)
                    ? new altitude_t[m_side * m_side]()
                    : nullptr} {
  if (m_side == 0)
    throw std::invalid_argument(
        "Terrain must have an odd side greater than 1");
}

dimension_t Terrain::side() const { return m_side; }
dimension_t Terrain::lines() const { return m_side; }
dimension_t Terrain::columns() const { return m_side; }

Terrain::~Terrain() {
  delete[] m_terrain;
  m_terrain = nullptr;
}
