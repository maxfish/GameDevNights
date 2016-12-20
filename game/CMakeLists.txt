cmake_minimum_required(VERSION 3.6)
project(GAME)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Setup SDL2
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

# Setup Engine
include_directories(engine/include)
file(GLOB ENGINE_SRC engine/src/*.cpp)

# Setup globals
include_directories(.)

# Build library
add_executable(GAME main.cpp ${ENGINE_SRC})
target_link_libraries(GAME ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
