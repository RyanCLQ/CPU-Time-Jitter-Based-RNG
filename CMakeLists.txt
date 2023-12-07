cmake_minimum_required(VERSION 3.9.0)

project(cpu-time-jitter-based-rng)

# global import header file
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# set the output location of compiled library file and header file
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
file(COPY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_BINARY_DIR}/out)

# files in library
aux_source_directory(src/jitterentropy rng_src)
aux_source_directory(src/ rng_src)

# static library
add_library(rng-static ${rng_src})
SET_TARGET_PROPERTIES(rng-static PROPERTIES OUTPUT_NAME "rng")

# dynamic library
add_library(rng SHARED ${rng_src})
target_link_libraries(rng PUBLIC pthread)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fPIC ")# 不能开启-O优化

add_executable(test test/test.c)
TARGET_LINK_LIBRARIES(test rng -lssl -lcrypto -lm)
