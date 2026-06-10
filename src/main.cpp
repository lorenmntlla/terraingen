#include "../include/palette.h"
#include <fstream>

int main() {
  std::ifstream file{"colors"};

  Palette fromFile{file};

  Color magenta{255, 0, 255};

  fromFile.addColor(magenta);
  fromFile.addColor(0, 255, 0);
  fromFile.addColor("#00FFFF");
  fromFile.addColor("FF0000");

  std::cout << "Palette with " << fromFile.getColorQuantity() << " colors\n";
  fromFile.printAllColors();
  bool get1{fromFile.printColor(14)};
  bool get2{fromFile.printColor(9)};

  std::cout << get1 << '\t' << get2 << '\n';
  return 0;
}
