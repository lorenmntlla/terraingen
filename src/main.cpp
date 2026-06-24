#include "../include/terrain.h"
#include "dimension.h"
#include <iostream>

int main(int argc, char **argv) {
  dimension_t side = (dimension_t)atoi(argv[1]);

  Terrain terreno{side};

  terreno.generate(atof(argv[2]));

  for (dimension_t height{0}; height < side * side; height++) {
    if (height % (side) == 0 and height != 0)
      std::cout << '\n';

    std::cout << (int)terreno.data()[height] << '\t';
  }

  std::cout << '\n';
  return 0;
}
