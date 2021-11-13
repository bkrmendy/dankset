cmake_minimum_required(VERSION 3.20)
project(hashset)

set(CMAKE_CXX_STANDARD 17)

add_library(hashset SHARED lib/Set.h)
set_target_properties(hashset PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()
add_subdirectory(test)