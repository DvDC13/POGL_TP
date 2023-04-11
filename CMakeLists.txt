cmake_minimum_required(VERSION 3.22.1)
project(pogl_tp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

add_library("${PROJECT_NAME}_lib" STATIC)
add_library("${PROJECT_NAME}_lib_vendor" STATIC)
target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories("${PROJECT_NAME}_lib_vendor" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(src)
add_subdirectory(vendor)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_lib" "${PROJECT_NAME}_lib_vendor" ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY})