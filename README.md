# Terraingen: Random Terrain Generator

## Requirements
- CMake 3.31 or better
- A C++23 compatible compiler

## Configure
```
cmake -S . -B build
```
add `-G "Ninja Multi-Config"` if you have Ninja.
or add `-DCMAKE_BUILD_TYPE=Release` for the Release compiler flags with generators such as make.

## Building
```
cmake --build build
```

## Installing
```
cmake --install
```
add `--config Release` if using Ninja Multi-Config.
