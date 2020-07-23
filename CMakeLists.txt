cmake_minimum_required(VERSION 3.15)
project(x11-example)
add_executable(demo main.cpp)
target_link_libraries(demo X11)