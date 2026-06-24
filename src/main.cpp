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
  Image red{side, side};
  Image green{side, side};
  Image blue{side, side};

  terreno.generate(atof(argv[2]));

  for (dimension_t height{0}; height < side * side; height++) {
    channel_t c{(channel_t)terreno.data()[height]};

    red.data()[height] = {c, 0, 0};
    green.data()[height] = {0, c, 0};
    blue.data()[height] = {0, 0, c};
  }

  red.savePPM("terrain_red.ppm");
  green.savePPM("terrain_green.ppm");
  blue.savePPM("terrain_blue.ppm");

  return 0;
}
