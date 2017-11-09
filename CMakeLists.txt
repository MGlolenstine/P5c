cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp P5c.h main.cpp)
add_executable(untitled ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${LIBPNG_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})

target_link_libraries(untitled ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${LIBPNG_LIBRARIES} ${PNG_LIBRARIES})