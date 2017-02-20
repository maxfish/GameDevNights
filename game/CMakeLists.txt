cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)
include(ExternalProject)

project(GAME)

# Setup SDL2
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(
        /usr/local/include
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

# Setup globals
include_directories(.)

# Gojira library
set(LIB_GOJIRA_SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/gojira-sdl2")
ExternalProject_Add(gojira-sdl2
        SOURCE_DIR ${LIB_GOJIRA_SDL2_DIR}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}"
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )
include_directories(${LIB_GOJIRA_SDL2_DIR})
file(GLOB_RECURSE GOJIRA_SDL2_SRC "${LIB_GOJIRA_SDL2_DIR}/*.cpp")

# Box2D library
set(LIB_BOX2D_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/box2d/Box2D/Box2D")
ExternalProject_Add(box2d
        SOURCE_DIR ${LIB_BOX2D_DIR}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}"
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/box2d/Box2D")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/box2d/Box2D/Box2D")
file(GLOB_RECURSE BOX2D_SRC "${LIB_BOX2D_DIR}/*.cpp")
file(GLOB_RECURSE BOX2D_INCLUDE "${LIB_BOX2D_DIR}/*.h")

# Setup Game
include_directories(game)
file(GLOB GAME_SRC game/*.cpp)
file(GLOB GAME_INCLUDES game/*.h)

# Build the game
add_executable(GAME main.cpp ${ENGINE_INCLUDES} ${GAME_SRC} ${GAME_INCLUDES} ${GOJIRA_SDL2_SRC} ${BOX2D_SRC})
add_dependencies(GAME gojira-sdl2 box2d)
target_link_libraries(GAME ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
