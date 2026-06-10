#include "../include/palette.h"
#include <iostream>
#include <fstream>

int main() {
  std::ifstream file{"colors"};

  Palette palette{file};

  Color magenta{255, 0, 255};

  palette.addColor(magenta);
  palette.addColor(0, 255, 0);
  palette.addColor("#00FFFF");
  palette.addColor("FF0000");

  std::cout << "Palette with " << palette.getColorQuantity() << " colors\n";
  palette.printAllColors();

  std::cout << "Attempting to print color with index 14:\n";
  bool get1{palette.printColor(14)};

  std::cout << "Attempting to print color with index 9:\n";
  bool get2{palette.printColor(9)};

  std::cout << get1 << '\t' << get2 << '\n';
  return 0;
}
