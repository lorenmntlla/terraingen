#include "../include/terrain.h"
#include "../include/parseNumber.h"
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <system_error>

Terrain::Terrain(dimension_t expoent)
    : m_side{(expoent > 0) ? (dimension_t)std::pow(2, expoent) + 1 : 0},
      m_rugosity{}, m_maxHeight{INT8_MAX}, m_range{},
      m_heightmap{(m_side > 0) ? new altitude_t[m_side * m_side]() : nullptr} {
  if (m_side < 3)
    throw std::invalid_argument("Expoent must be greater than 0. Received: " +
                                std::to_string(expoent));
}

Terrain::~Terrain() {
  delete[] m_heightmap;
  m_heightmap = nullptr;
}

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) const {
  return m_heightmap[y * m_side + x];
}

altitude_t &Terrain::operator()(dimension_t x, dimension_t y) {
  return m_heightmap[y * m_side + x];
}

bool Terrain::saveFile(const std::string &fileName) const {
  std::ofstream file{fileName};

  if (!file) {
    auto err{errno};
    std::cerr << "Could not open " << fileName;

    if (err != 0)
      std::cerr << ": " << std::generic_category().message(err);

    std::cerr << '\n';
    return false;
  }

  file << "T1\n";
  file << m_side << '\n';
  file << (int)m_maxHeight << '\n';

  const long heightmap_Size{(long)(m_side * m_side)};
  file.write(reinterpret_cast<char *>(m_heightmap), heightmap_Size);

  return true;
}

bool Terrain::readFile(const std::string &fileName) {
  std::ifstream file{fileName};

  if (!file) {
    auto err{errno};
    std::cerr << "Could not open " << fileName;

    if (err != 0)
      std::cerr << ": " << std::generic_category().message(err);

    std::cerr << '\n';
    return false;
  }

  std::string current{};

  file >> current;

  if (current != "T1") {
    std::cerr << fileName << ' ' << "Unknown file format: " << current << '\n';

    return false;
  }

  file >> current;
  const dimension_t side{parseNumber<dimension_t>(current)};
  const double pow{(std::log(side - 1) / std::log(2))};

  if (pow != std::floor(pow)) {
    std::cerr << fileName << ": "
              << "Terrain dimension must be (2^n) + 1. Received: " << current
              << '\n';

    return false;
  }

  file >> current;
  const altitude_t maxHeight{parseNumber<altitude_t>(current)};

  if (maxHeight < 0) {
    std::cerr << fileName << ": "
              << "Max Height must be greater than 0. Received: " << current
              << '\n';

    return false;
  }

  m_side = side;
  m_maxHeight = maxHeight;

  delete[] m_heightmap;
  m_heightmap = new altitude_t[m_side * m_side];

  const long heightmap_Size{(long)(m_side * m_side)};
  file.read(reinterpret_cast<char *>(m_heightmap), heightmap_Size);

  if (file.fail()) {
    std::cerr << fileName << ": " << "Could not read whole terrain.\n"
              << "Expected: " << heightmap_Size << " Read: " << file.gcount()
              << '\n';

    return false;
  }

  return true;
};

bool Terrain::generate(double rugosity) {
  if (rugosity < 0 or rugosity > 1)
    throw std::invalid_argument(
        "Rugosity must be between 0 and 1 inclusive. Received: " +
        std::to_string(rugosity));

  m_rugosity = rugosity;
  m_range = m_maxHeight;

  const dimension_t boundary{m_side - 1};

  operator()(0, 0) = noise();
  operator()(0, boundary) = noise();
  operator()(boundary, 0) = noise();
  operator()(boundary, boundary) = noise();

  for (dimension_t chunk{boundary}; chunk > 1; chunk /= 2) {
    diamond(chunk);
    square(chunk);

    m_range = altitude_t(m_range * m_rugosity);
  }

  return true;
}

dimension_t Terrain::side() const { return m_side; }

dimension_t Terrain::lines() const { return m_side; }

dimension_t Terrain::columns() const { return m_side; }

altitude_t *Terrain::data() { return m_heightmap; }

altitude_t Terrain::noise() const {
  thread_local std::random_device rd{};
  thread_local std::seed_seq seed{
      static_cast<std::seed_seq::result_type>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count()),
      rd(),
      rd(),
      rd(),
      rd(),
      rd(),
      rd(),
      rd()};
  thread_local std::mt19937 generator{seed};

  std::uniform_int_distribution<altitude_t> dist{
      static_cast<altitude_t>(-m_range), m_range};

  return dist(generator);
}

void Terrain::diamond(dimension_t chunk) {
  const dimension_t bound{m_side - 1};
  const dimension_t half{chunk / 2};

  for (dimension_t dy{0}; dy < bound; dy += chunk) {
    for (dimension_t dx{0}; dx < bound; dx += chunk) {
      const altitude_t upperLeft = operator()(dx, dy);
      const altitude_t upperRight = operator()(dx + chunk, dy);
      const altitude_t bottomLeft = operator()(dx, dy + chunk);
      const altitude_t bottomRight = operator()(dx + chunk, dy + chunk);

      altitude_t &center = operator()(dx + half, dy + half);
      center = static_cast<altitude_t>(
          (upperLeft + upperRight + bottomLeft + bottomRight) / 4 + noise());
    }
  }
}

void Terrain::square(dimension_t chunk) {
  const dimension_t bound{m_side - 1};
  const dimension_t half{chunk / 2};

  for (dimension_t dy{0}; dy <= bound; dy += half) {
    dimension_t dxStart{(dy % chunk == 0) ? half : 0};

    for (dimension_t dx{dxStart}; dx <= bound; dx += chunk) {
      altitude_t sum{0};
      altitude_t count{0};

      if (dy >= half) {
        sum += operator()(dx, dy - half);
        count++;
      }
      if (dy + half <= bound) {
        sum += operator()(dx, dy + half);
        count++;
      }
      if (dx >= half) {
        sum += operator()(dx - half, dy);
        count++;
      }
      if (dx + half <= bound) {
        sum += operator()(dx + half, dy);
        count++;
      }

      operator()(dx, dy) = static_cast<altitude_t>((sum / count) + noise());
    }
  }
}
