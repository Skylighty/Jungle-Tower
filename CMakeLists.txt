cmake_minimum_required(VERSION 3.17)
project(platformowka_again)

#set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)


add_executable(platformowka_again src/main.cpp src/game.cpp src/game.h src/player.cpp src/player.h)
target_link_libraries(platformowka_again sfml-graphics sfml-audio sfml-system sfml-window -static)