cmake_minimum_required(VERSION 3.10)

# set the project name
project(Math)

# Add custom math library
add_library(mathlib add.c sub.c)

# add the executable
add_executable(app main.c)

target_link_libraries(app PUBLIC mathlib)
