cmake_minimum_required(VERSION 3.20)
project(udp_socket)

set(CMAKE_CXX_STANDARD 14)

add_executable(client client.cpp)
add_executable(server server.cpp)
