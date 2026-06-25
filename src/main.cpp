#include "../include/terrain.h"
#include "color.h"
#include "dimension.h"
#include "image.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: " << "terraingen" << " side rugosity\n";
    return 1;
  }

  dimension_t side = (dimension_t)atoi(argv[1]);

  Terrain terreno{side};
  Image canvas{side, side};

  Image red{side, side};
  Image green{side, side};
  Image blue{side, side};

  terreno.generate(atof(argv[2]));

  const dimension_t totalPoints{side * side};
  for (dimension_t point{0}; point < totalPoints; point++) {
    const altitude_t red_mask{0b0000'0110};
    const altitude_t green_mask{0b0110'0000};
    const altitude_t blue_mask{0b0001'1000};

    const altitude_t height{terreno.data()[point]};

    const channel_t r{(channel_t)((height & red_mask))};
    const channel_t g{(channel_t)(height & green_mask)};
    const channel_t b{(channel_t)(height & blue_mask)};
    const channel_t c{(channel_t)(height)};

    canvas.data()[point] = {r, g, b};
    red.data()[point] = {c, 0, 0};
    green.data()[point] = {0, c, 0};
    blue.data()[point] = {0, 0, c};
  }

  canvas.savePPM("terrain.ppm");
  red.savePPM("terrain_red.ppm");
  green.savePPM("terrain_green.ppm");
  blue.savePPM("terrain_blue.ppm");

  return 0;
}
