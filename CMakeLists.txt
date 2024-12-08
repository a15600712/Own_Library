# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(PQC_LIB C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compile options
add_compile_options(-Wall -Wextra -g)

# Exclude verification directory from build
set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL "${CMAKE_SOURCE_DIR}/verification")

# Library source files
set(LIB_SOURCES
    src/arithmetic.c
    src/ntt.c
    src/poly.c
    src/zetas.c
)

# Create library
add_library(pqc_lib_core ${LIB_SOURCES})

# Set include directories for the library
target_include_directories(pqc_lib_core 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create executable
add_executable(PQC_LIB src/main.c)

# Link the library
target_link_libraries(PQC_LIB PRIVATE pqc_lib_core)