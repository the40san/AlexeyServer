cmake_minimum_required(VERSION 2.8)
add_definitions("-Wall -std=c++14")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(util
  logger.cpp
)
