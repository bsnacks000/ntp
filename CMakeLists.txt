cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME ntp)
project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_C_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(LIBRARY_NAME ntp)

add_library(${LIBRARY_NAME} STATIC ntp.c)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_SOURCE_DIR}")
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
enable_testing()

add_executable(test_ntp test.c)
target_compile_options(test_ntp PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(test_ntp PRIVATE ntp)

add_test(NAME test_ntp COMMAND test_ntp)