#include "../include/terrain.h"
#include "color.h"
#include "dimension.h"
#include "image.h"
#include <cmath>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: " << "terraingen" << " side rugosity\n";
    return 1;
  }

  const dimension_t expoent = (dimension_t)atoi(argv[1]);

  const dimension_t side{(dimension_t)std::pow(2, expoent) + 1};

  Terrain map{expoent};

  map.generate(atof(argv[2]));

  map.saveFile("terreno.alt");

  Terrain terreno{};

  terreno.readFile("terreno.alt");

  Image canvas{side, side};

  const dimension_t totalPoints{side * side};
  for (dimension_t point{0}; point < totalPoints; point++) {
    const altitude_t red_mask{0b0000'0110};
    const altitude_t green_mask{0b0110'0000};
    const altitude_t blue_mask{0b0001'1000};

    const altitude_t height{terreno.data()[point]};

    const channel_t r{(channel_t)((height & red_mask))};
    const channel_t g{(channel_t)(height & green_mask)};
    const channel_t b{(channel_t)(height & blue_mask)};

    canvas.data()[point] = {r, g, b};
  }

  canvas.savePPM("terrain.ppm");

  return 0;
}
