#include "../include/image.h"

int main() {
  Image img{1920, 1200};

  Palette sunset("sunset_flag.hex");

  Palette trans("trans_flag.hex");

  for (size_t i{0}; i < img.length(); i++) {
    for (size_t j{0}; j < img.height() / 5; j++) {
      img.setPixel(i, j, *sunset.getColor(0));
      img.setPixel(i, j + img.height() / 5, *sunset.getColor(1));
      img.setPixel(i, j + (img.height() / 5) * 2, *sunset.getColor(2));
      img.setPixel(i, j + (img.height() / 5) * 3, *sunset.getColor(3));
      img.setPixel(i, j + (img.height() / 5) * 4, *sunset.getColor(4));
    }
  }

  img.savePPM("sunset");

  for (size_t i{0}; i < img.length(); i++) {
    for (size_t j{0}; j < img.height() / 5; j++) {
      img.setPixel(i, j, *trans.getColor(0));
      img.setPixel(i, j + img.height() / 5, *trans.getColor(1));
      img.setPixel(i, j + (img.height() / 5) * 2, *trans.getColor(2));
      img.setPixel(i, j + (img.height() / 5) * 3, *trans.getColor(3));
      img.setPixel(i, j + (img.height() / 5) * 4, *trans.getColor(4));
    }
  }

  img.savePPM("trans");

  return 0;
}
