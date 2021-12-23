cmake_minimum_required(VERSION 3.14)
message("Running CMake version ${CMAKE_VERSION}")

#########################
# General CMake settings

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Make only Debug/Release valid in IDEs
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")


#########################
# Project

project(factorio-starcraft-assettool
    VERSION 1.0.0
    HOMEPAGE_URL https://github.com/heinermann/factorio-starcraft-assettool
)

#########################
# Dependencies

set(CASC_BUILD_STATIC_LIB ON CACHE BOOL "Build static linked library")
set(CASC_BUILD_SHARED_LIB OFF CACHE BOOL "Compile dynamically linked library")
add_subdirectory(CascLib)

find_package(PNG REQUIRED)

add_library(dds_reader STATIC EXCLUDE_FROM_ALL
    simple-dds-image-reader/ddsreader.cpp
    simple-dds-image-reader/ddsreader.hpp
)

#########################
# Converter

file(GLOB_RECURSE SRC_FILES factorio-starcraft-tool/*.cpp)
file(GLOB_RECURSE HEADER_FILES factorio-starcraft-tool/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/factorio-starcraft-tool PREFIX "Source Files" FILES ${CPP_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/factorio-starcraft-tool PREFIX "Header Files" FILES ${HEADER_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} casc_static PNG::PNG dds_reader pthread tbb)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    cimg_use_png
    cimg_display=0
)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
