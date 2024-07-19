cmake_minimum_required(VERSION 3.10.2)

project(SelfDrivingCar)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/csfml)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC external/csfml/include PUBLIC include)

add_subdirectory(tests)