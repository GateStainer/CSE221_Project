cmake_minimum_required(VERSION 3.10)
project(CSE221_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(CSE221_Project cpu/cpu.h memory/memory.h main.c cpu/cpu.c memory/memory.c)