cmake_minimum_required(VERSION 3.31...4.3)
project(terraingen VERSION 0.0.2 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(APP_NAME "terraingen")

set(COMPILE_OPTIONS "-pipe" "-Wall" "-Wextra" "-Wabi" "-Wconversion" "-pedantic" "-Wfatal-errors" "-g3" "-O0")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB SOURCES "src/*.cpp")

add_executable(${APP_NAME} ${SOURCES})
target_compile_options(${APP_NAME} PRIVATE ${COMPILE_OPTIONS})
