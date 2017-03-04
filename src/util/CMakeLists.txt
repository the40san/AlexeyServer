cmake_minimum_required(VERSION 3.1)
add_definitions("-Wall")
set (CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(util
  logger.cpp
)
