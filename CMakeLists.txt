cmake_minimum_required(VERSION 3.25)
project(jak_dojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(jak_dojade main.cpp my-stl/stl_lib/vector.hxx my-stl/stl_lib/vstring.cpp my-stl/stl_lib/pair.hxx my-stl/stl_lib/linkedList.hxx my-stl/stl_lib/pair.h my-stl/stl_lib/linkedList.h howToGo.cpp howToGo.h graph.cpp graph.h my-stl/stl_lib/priorityQueue.h my-stl/stl_lib/hashMap.h my-stl/stl_lib/hashMap.cpp my-stl/stl_lib/priorityQueue.hxx)
