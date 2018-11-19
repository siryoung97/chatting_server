cmake_minimum_required(VERSION 3.12)
project(PROJECT C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY binary)

set(CMAKE_CURRENT_BINARY_DIR binary)

add_executable(client client.c)

add_executable(server server.c)
