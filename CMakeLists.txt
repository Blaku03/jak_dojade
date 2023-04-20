cmake_minimum_required(VERSION 3.25)
project(jak_dojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(jak_dojade main.cpp my-stl/stl_lib/vector.hxx my-stl/stl_lib/vstring.cpp my-stl/stl_lib/pair.hxx my-stl/stl_lib/LinkedList.hxx my-stl/stl_lib/pair.h my-stl/stl_lib/LinkedList.h howToGo.cpp howToGo.h)
