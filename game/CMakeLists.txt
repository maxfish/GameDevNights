cmake_minimum_required(VERSION 3.6)
project(GAME)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCE_FILES main.cpp
        globals.h
        source/game.h
        source/game.cpp
        source/sprite.h
        source/sprite.cpp
        source/input.h
        source/input.cpp
        source/graphics.h
        source/graphics.cpp
        source/FramesStore.h
        source/FramesStore.cpp
        source/Animation.h
        source/Animation.cpp
        source/Frame.h
        source/Frame.cpp
        )

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

add_executable(GAME ${SOURCE_FILES})
target_link_libraries(GAME ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
