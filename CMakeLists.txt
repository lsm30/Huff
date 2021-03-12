# @file CMakeLists.txt
# 
# CMake files for member initialization list examples

cmake_minimum_required(VERSION 3.10)

# project info
project(InitList)

# C++17
set(CMAKE_CXX_STANDARD 17)

# Source files for the main program srcFacts
set(SOURCE main.cpp HuffmanTree.cpp)



# Turn on warnings
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # standard warnings
    add_compile_options(-Wall -Wno-unused-private-field -Wno-unused-variable)
endif()

# Assume each .cpp file is a separate application
file(GLOB APPLICATIONS "*.cpp")


# srcFact application
add_executable(main ${SOURCE})

# Demo run command
add_custom_target(run
        COMMENT "Run demo"
        COMMAND ./main
        DEPENDS main
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

