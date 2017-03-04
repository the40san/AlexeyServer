cmake_minimum_required(VERSION 3.1)
add_definitions("-Wall")
set (CMAKE_CXX_STANDARD 14)

add_subdirectory(util)
add_subdirectory(network)
add_subdirectory(message)

add_executable(main
  main.cpp
  server.cpp
)

target_link_libraries(main network message util)
