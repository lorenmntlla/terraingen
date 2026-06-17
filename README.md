# Terraingen: Random Terrain Generator

## Requirements
- CMake 3.31 or better.
- A C++23 compatible compiler.

## Configure
```
cmake -S . -B build
```
Add `-G "Ninja Multi-Config"` if you have Ninja.
Alternatively, add `-DCMAKE_BUILD_TYPE=Release` for the Release compiler flags with generators such as make.

## Building
```
cmake --build build
```
