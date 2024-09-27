cmake_minimum_required(VERSION 3.20)
project(ProgettoAPI C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -static-libasan")

add_executable(ProgettoAPI main.c)
