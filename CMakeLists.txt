cmake_minimum_required(VERSION 3.1)

project(virtual_light)

add_compile_options(-std=c++11)

add_definitions("-Wall -g")

aux_source_directory(src/ SRC)

add_executable(virtual_light ${SRC})