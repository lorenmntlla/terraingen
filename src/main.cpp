#include "../include/image.h"

void drawStripes(Image &img, const Palette &palette) {
  if (palette.size() == 0)
    return;

  const dimension_t width{img.length()};
  const dimension_t height{img.height()};
  const size_t numColors{palette.size()};
  const dimension_t stripeHeight = height / numColors;

  for (size_t color{0}; color < numColors; color++) {
    const auto currentColor = *palette.getColor(color);

    const dimension_t startY = color * stripeHeight;
    const dimension_t endY =
        (color == numColors - 1) ? height : startY + stripeHeight;

    for (dimension_t y{startY}; y < endY; y++)
      for (dimension_t x{0}; x < width; x++)
        img(x, y) = currentColor;
  }
}

int main() {
  Image canvas{1920, 1200};

  Palette sunset{"sunset_flag.hex"};

  Palette gay{"gay_flag.hex"};

  Palette trans{"trans_flag.hex"};

  Palette pride{"pride.hex"};

  Palette non_binary{"non_binary.hex"};

  drawStripes(canvas, sunset);

  canvas.savePPM("sunset.ppm");

  drawStripes(canvas, trans);

  canvas.savePPM("trans.ppm");

  drawStripes(canvas, pride);

  canvas.savePPM("pride.ppm");

  drawStripes(canvas, non_binary);

  canvas.savePPM("non_binary.ppm");

  drawStripes(canvas, gay);

  canvas.savePPM("gay_flag.ppm");

  return 0;
}
