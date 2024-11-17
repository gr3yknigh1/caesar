cmake_minimum_required(VERSION 3.20)
project(caesar LANGUAGES C)

option(BUILD_TESTS "Build with tests" ON)

add_library(caesar
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/caesar.c
  ${CMAKE_CURRENT_SOURCE_DIR}/caesar.h
)
target_include_directories(caesar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(caesar PUBLIC c_std_99)

add_executable(caesar_cli
  ${CMAKE_CURRENT_SOURCE_DIR}/caesar_cli.c
)

target_link_libraries(caesar_cli PRIVATE caesar)

if(BUILD_TESTS)
  enable_testing()
  find_package(nocheck REQUIRED CONFIG)

  foreach(CAESAR_TEST_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_basic.c
  )
    get_filename_component(CAESAR_TEST_NAME ${CAESAR_TEST_SOURCE} NAME_WE)
    add_executable(${CAESAR_TEST_NAME} ${CAESAR_TEST_SOURCE})

    target_link_libraries(
      ${CAESAR_TEST_NAME}
      PRIVATE nocheck::nocheck
      PRIVATE caesar
    )

    add_test(${CAESAR_TEST_NAME} ${CAESAR_TEST_NAME})
  endforeach()
endif()
