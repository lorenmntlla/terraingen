#include "../include/image.h"
#include "../include/palette.h"

int main() {
  Image test{10, 15};
  Palette storage;

  storage.addColor(test.getPixel(4, 5));
  storage.printColor(0);

  test.setPixel(4, 5, {0, 128, 0});
  storage.addColor(test.getPixel(4, 5));
  storage.printColor(1);
}
