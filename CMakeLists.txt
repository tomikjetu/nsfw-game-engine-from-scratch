cmake_minimum_required(VERSION 3.23)
project(Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Game
        include/Entity.hpp
        include/RenderWindow.hpp
        include/Vector2d.hpp
        src/entity.cpp
        src/main.cpp
        src/renderwindow.cpp
        src/Vector2d.cpp)
