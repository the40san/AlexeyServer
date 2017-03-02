cmake_minimum_required(VERSION 2.8)
add_definitions("-Wall -std=c++14 -g")

add_subdirectory(util)
add_subdirectory(network)
add_subdirectory(message)

add_executable(main
  main.cpp
  server.cpp
)

target_link_libraries(main util network message)
