# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)

PROJECT(NTT)

# Add math library
find_library(MATH_LIBRARY m)

# Add lib subdirectory before creating the executable
add_subdirectory(libs)

# Create main executable
add_executable(${PROJECT_NAME} main.c)

# Link main executable with our library and math library
target_link_libraries(${PROJECT_NAME} 
    PRIVATE libs
    PRIVATE ${MATH_LIBRARY}
)

# Add include directories for the main executable
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/libs
)