cmake_minimum_required(VERSION 2.8.9)
project(server)

file(GLOB SOURCES "*.c")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
