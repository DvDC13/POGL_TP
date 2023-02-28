cmake_minimum_required(VERSION 3.22.1)
project(pogl_tp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

add_library("${PROJECT_NAME}_lib" STATIC)
target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_lib" ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY})