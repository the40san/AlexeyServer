cmake_minimum_required(VERSION 2.8)
add_definitions("-Wall -std=c++14")

add_library(network
  socket.cpp
  unix_socket_receiver.cpp
)

target_include_directories(network
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
