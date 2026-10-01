cmake_minimum_required(VERSION 3.20)
project(ne-lattice VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(lattice INTERFACE)
add_library(ne_pp::lattice ALIAS lattice)

target_include_directories(lattice INTERFACE include)