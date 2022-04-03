cmake_minimum_required(VERSION 3.13)
project(tests)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS system REQUIRED)
link_directories(${Boost_LIBRARY_DIR})

include_directories(../include)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

enable_testing()
add_executable(test_ringbuffer_push_back test_ringbuffer_push_back.cpp)
add_executable(test_ringbuffer_iterators test_ringbuffer_iterators.cpp)
add_executable(test_ringbuffer_standart_alorithms test_ringbuffer_standart_alorithms.cpp)

add_test(NAME ringbuffer_push_back COMMAND test_ringbuffer_push_back)
add_test(NAME ringbuffer_iterators COMMAND test_ringbuffer_iterators)
add_test(NAME ringbuffer_standart_alorithms COMMAND test_ringbuffer_standart_alorithms)
