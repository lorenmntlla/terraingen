#include "../include/terrain.h"
#include "dimension.h"
#include "palette.h"
#include "parseNumber.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cout << "Usage: " << "terraingen"
              << " output palette side [seed] [rugosity]\n";
    return 1;
  }

  const dimension_t expoent{parseNumber<dimension_t>(argv[3])};

  Terrain terrain{expoent};

  if (argc > 4) {
    unsigned long seed{parseNumber<unsigned long>(argv[4])};
    terrain.setSeed(seed);
  }

  if (argc > 5)
    terrain.generate(atof(argv[5]));
  else
    terrain.generate(0.625);

  Palette palette{argv[2]};

  terrain.image(palette).savePPM(argv[1]);

  return 0;
}
