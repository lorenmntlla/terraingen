#include "../include/terrain.h"
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>

altitude_t Terrain::noise() {
  std::mt19937 generator{std::random_device{}()};
  std::uniform_int_distribution<altitude_t> dist{(altitude_t)-m_range, m_range};

  return dist(generator);
}

Terrain::Terrain(dimension_t side)
    : m_side{(side > 2 and ((side - 1) & (side - 2)) == 0) ? side : 0},
      m_rugosity{0}, m_range{INT8_MAX},
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

bool Terrain::saveFile(const std::string &fileName) const {};

bool Terrain::generate(double rugosity) {
  if (rugosity < 0 or rugosity > 1)
    throw std::invalid_argument(
        "Rugosity must be between 0 and 1 inclusive. Received" +
        std::to_string(rugosity));

  m_rugosity = rugosity;

  const dimension_t boundary{m_side - 1};

  operator()(0, 0) = noise();
  operator()(0, boundary) = noise();
  operator()(boundary, 0) = noise();
  operator()(boundary, boundary) = noise();

  diamondSquare();

  return true;
}

void Terrain::diamondSquare() {
  const dimension_t boundary{m_side - 1};

  for (dimension_t bound{boundary}; bound > 1; bound /= 2) {
    const dimension_t half{bound / 2};

    // Diamond
    for (dimension_t dy{0}; dy < boundary; dy += bound) {
      for (dimension_t dx{0}; dx < boundary; dx += bound) {
        const altitude_t upperLeft = operator()(dx, dy);
        const altitude_t upperRight = operator()(dx + bound, dy);
        const altitude_t bottomLeft = operator()(dx, dy + bound);
        const altitude_t bottomRight = operator()(dx + bound, dy + bound);

        altitude_t &center = operator()(dx + half, dy + half);
        center =
            (upperLeft + upperRight + bottomLeft + bottomRight) / 4 + noise();
      }
    }

    // Square
    for (dimension_t dy{0}; dy <= boundary; dy += half) {
      dimension_t dxStart{(dy % bound == 0) ? half : 0};

      for (dimension_t dx{dxStart}; dx <= boundary; dx += bound) {
        altitude_t sum{0};
        altitude_t count{0};

        if (dy >= half) {
          sum += operator()(dx, dy - half);
          count++;
        }
        if (dy + half <= boundary) {
          sum += operator()(dx, dy + half);
          count++;
        }
        if (dx >= half) {
          sum += operator()(dx - half, dy);
          count++;
        }
        if (dx + half <= boundary) {
          sum += operator()(dx + half, dy);
          count++;
        }

        operator()(dx, dy) = (sum / count) + noise();
      }
    }

    // Apply rugosity
    m_range = altitude_t(m_range * m_rugosity);
  }
}

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) {
  return m_heightmap[y * m_side + x];
}

bool Terrain::readFile(const std::string &fileName) {};

altitude_t *Terrain::data() { return m_heightmap; }

Terrain::~Terrain() {
  delete[] m_heightmap;
  m_heightmap = nullptr;
}
