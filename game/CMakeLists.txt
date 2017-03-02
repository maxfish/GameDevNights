project(GAME CXX)
cmake_minimum_required(VERSION 3.6)
include(ExternalProject)
set(CMAKE_CXX_STANDARD 11)

################################################################
# SDL2                                                         #
################################################################
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

################################################################
# External libraries                                           #
################################################################
set(GOJIRA_SDL2_DIR "externals/gojira-sdl2")
add_subdirectory(${GOJIRA_SDL2_DIR})
include_directories(${GOJIRA_SDL2_DIR})
file(GLOB_RECURSE GOJIRA_SDL2_SRC
        "${GOJIRA_SDL2_DIR}/engine/*.cpp"
        "${GOJIRA_SDL2_DIR}/externals/SpriterPlusPlus/spriterengine/*.cpp"
        "${GOJIRA_SDL2_DIR}/externals/box2d/Box2D/Box2D/*.cpp"
        )
include_directories(${GOJIRA_SDL2_DIR}/externals/box2d/Box2D)
include_directories(${GOJIRA_SDL2_DIR}/externals/SpriterPlusPlus)
include_directories(${GOJIRA_SDL2_DIR}/third_parties)

# Setup Game
include_directories(./game)
file(GLOB GAME_SRC game/*.cpp)

# Build the game
add_executable(GAME main.cpp ${ENGINE_INCLUDES} ${GAME_SRC} ${GOJIRA_SDL2_SRC})
target_link_libraries(GAME ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
