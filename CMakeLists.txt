cmake_minimum_required(VERSION 3.0)
project(iglib)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(iglib)

file(GLOB_RECURSE EXAMPLES "src/*.cpp")

foreach(EXAMPLE ${EXAMPLES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
  add_executable(${EXAMPLE_NAME} ${EXAMPLE})
  target_link_libraries(${EXAMPLE_NAME} iglib)
  target_include_directories(${EXAMPLE_NAME} PUBLIC iglib include)
endforeach()
