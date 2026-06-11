#include "../include/image.h"

int main() {
  Image img{1920, 1200};

  Palette sunset("sunset_flag.hex");

  Palette trans("trans_flag.hex");

  for (size_t i{0}; i < 1920; i++) {
    for (size_t j{0}; j < 240; j++) {
      img.setPixel(i, j, *sunset.getColor(0));
      img.setPixel(i, j + 240, *sunset.getColor(1));
      img.setPixel(i, j + 480, *sunset.getColor(2));
      img.setPixel(i, j + 720, *sunset.getColor(3));
      img.setPixel(i, j + 960, *sunset.getColor(4));
    }
  }

  img.savePPM("sunset");

  for (size_t i{0}; i < 1920; i++) {
    for (size_t j{0}; j < 240; j++) {
      img.setPixel(i, j, *trans.getColor(0));
      img.setPixel(i, j + 240, *trans.getColor(1));
      img.setPixel(i, j + 480, *trans.getColor(2));
      img.setPixel(i, j + 720, *trans.getColor(3));
      img.setPixel(i, j + 960, *trans.getColor(4));
    }
  }

  img.savePPM("trans");

  return 0;
}
