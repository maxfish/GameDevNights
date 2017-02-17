cmake_minimum_required(VERSION 3.6)
project(GAME)

include(ExternalProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

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

# Setup Game
include_directories(game/include)
file(GLOB GAME_SRC game/src/*.cpp)
file(GLOB GAME_INCLUDES game/include/*.h)

# Setup globals
include_directories(.)

# Gojira library
set(GOJIRA_SDL2_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}")
ExternalProject_Add(gojira_sdl2
        GIT_REPOSITORY https://github.com/maxfish/gojira-sdl2.git
        INSTALL_DIR ${GOJIRA_SDL2_INSTALL_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )
file(GLOB_RECURSE GOJIRA_SDL2_LIBRARY "${GOJIRA_SDL2_INSTALL_DIR}/libgojira_sdl2.a")
ExternalProject_Get_Property(gojira_sdl2 source_dir)
include_directories(${source_dir})

# Build library
add_executable(GAME main.cpp ${ENGINE_INCLUDES} ${GAME_SRC} ${GAME_INCLUDES})
add_dependencies(GAME gojira_sdl2)
target_link_libraries(GAME ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${GOJIRA_SDL2_LIBRARY}
        )
