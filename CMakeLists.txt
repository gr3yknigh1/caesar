cmake_minimum_required(VERSION 3.20)
project(caesar LANGUAGES C)

add_executable(caesar
  ${CMAKE_CURRENT_SOURCE_DIR}/caesar.c
)
