cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

project (cpp-utils)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::cpp-utils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)