cmake_minimum_required(VERSION 3.31...4.3)

project(terraingen VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(APP_NAME "terraingen")

set(COMPILE_OPTIONS "-pipe" "-Wall" "-Wextra" "-Wabi" "-Wconversion" "-pedantic" "-Wfatal-errors")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(palette src/palette.cpp include/palette.h include/color.h)
target_compile_options(palette PRIVATE ${COMPILE_OPTIONS})

add_library(image src/image.cpp include/image.h include/color.h include/dimension.h)
target_compile_options(image PRIVATE ${COMPILE_OPTIONS})

add_executable(${APP_NAME} src/main.cpp)
target_include_directories(${APP_NAME} PRIVATE include)
target_link_libraries(${APP_NAME} PRIVATE palette image)
target_compile_options(${APP_NAME} PRIVATE ${COMPILE_OPTIONS})
