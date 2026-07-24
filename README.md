# Terraingen: Procedural Terrain Generator
A fast, lightweight procedural 2D terrain generator written in C++.
Uses the Diamond-Square algorithm to create realistic fractal heightmaps,
applies customizable hex-based color palettes,
and outputs shaded heightmaps directly as Netpbm PPM images.

## Features

* **Diamond-Square Algorithm:** Generates procedural heightmap
meshes with adjustable roughness (`rugosity`).
* **Custom Color Palettes:** Read color gradations dynamically from plain 
`.hex` color palette files.
* **Built-in Shading:** Automatically applies simple top-left directional 
hill-shading for added depth and contrast.
* **PPM Image Export:** Renders maps directly to standard ASCII 
Netpbm `.ppm` format files.
* **Binary File I/O:** Native support for saving and loading raw binary 
heightmap files (`.hgm`).
* **Modern C++23:** Built using modern C++ abstractions and strict compiler warning standardizations.

## Requirements
- CMake 3.31 or higher
- A C++23 compatible compiler (e.g., GCC 13+, Clang 17+, or MSVC 2022+)

## Building
```shell
cmake -B build
cmake --build build
```

## Usage
```shell
$ ./terraingen <output_file> <palette_file> <exponent> [seed] [rugosity]
```

## Palette Format
Color palettes are plain text files containing hex codes (formatted as #RRGGBB).
Colors are mapped sequentially to terrain altitudes from lowest to highest.

Example (`default.hex` excerpt):

```plaintext
#71abd8
#79b2de
#acd0a5
#93bf8b
#bdcc96
#ffffff
```

