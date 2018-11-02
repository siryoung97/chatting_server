cmake_minimum_required(VERSION 3.12)
project(chatting_server C)

set(CMAKE_C_STANDARD 11)

add_executable(chatting_server client.c server.c)