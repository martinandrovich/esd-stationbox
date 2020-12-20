# serialib library
set(serialib_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "serialib_INCLUDE_DIR")
add_library(serialib serialib.cpp)
target_include_directories(serialib PUBLIC ${serialib_INCLUDE_DIR})