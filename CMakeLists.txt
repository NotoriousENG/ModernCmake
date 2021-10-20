cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ModernCmake VERSION 1.0)

# add the executable
add_executable(ModernCmake main.cpp)

add_subdirectory(Adder)

target_include_directories(${PROJECT_NAME} PRIVATE Adder/)

target_link_directories(${PROJECT_NAME} PRIVATE Adder/)

target_link_libraries(${PROJECT_NAME} adder)