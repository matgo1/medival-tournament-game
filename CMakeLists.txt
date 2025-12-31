cmake_minimum_required(VERSION 3.10)
project(Tournament VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(tournament
    main.cpp
    entities.cpp
)

# Copy the names.txt file to build directory
configure_file(names.txt ${CMAKE_CURRENT_BINARY_DIR}/names.txt COPYONLY)