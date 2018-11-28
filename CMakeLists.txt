cmake_minimum_required(VERSION 3.10)
project(CSE221_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(cpu cpu/cpu.h cpu/main.c cpu/cpu.c)
add_executable(memory memory/memory.h memory/main.c memory/memory.c)