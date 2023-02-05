cmake_minimum_required(VERSION 3.25...3.26)

project(Cpp23examples LANGUAGES CXX)

enable_testing()

include(cmake/compilers.cmake)

add_subdirectory(cpp14)
add_subdirectory(cpp17)
add_subdirectory(cpp20)
add_subdirectory(cpp23)
