cmake_minimum_required(VERSION 3.14)
project(Jungle-Tower)

set(SFML_DIR "C:/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/game.h src/player.cpp src/player.h src/platform.cpp src/platform.h src/feature.cpp src/feature.h)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)