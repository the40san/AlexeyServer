cmake_minimum_required(VERSION 3.1)
add_definitions("-Wall")
set (CMAKE_CXX_STANDARD 14)

add_library(network
  socket.cpp
  unix_socket_receiver.cpp
)

target_include_directories(network
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
