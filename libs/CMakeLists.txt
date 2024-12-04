# libs/CMakeLists.txt
add_library(libs
    zetas.c 
    exp_mod.c
)

# Add include directories for the library
target_include_directories(libs
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link math library to our library as well since we use math functions
target_link_libraries(libs
    PUBLIC ${MATH_LIBRARY}
)