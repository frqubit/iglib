file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(iglib ${LIB_SOURCES})

target_include_directories(iglib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(iglib PUBLIC
  sfml-graphics
  sfml-window
  sfml-system
)