cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp P5c.h cat.png die.png README.md sun.png)
add_executable(untitled ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#find_package(IL REQUIRED)

FIND_PATH(IL_INCLUDE_DIRS il.h PATH_SUFFIXES include IL DOC "The path the the directory that contains il.h")
FIND_LIBRARY(IL_LIBRARIES NAMES IL DEVIL PATH_SUFFIXES lib64 lib lib32 DOC "The file that corresponds to the base il library.")

FIND_LIBRARY(ILUT_LIBRARIES NAMES ILUT PATH_SUFFIXES lib64 lib lib32 DOC "The file that corresponds to the il (system?) utility library.")
FIND_LIBRARY(ILU_LIBRARIES NAMES ILU PATH_SUFFIXES lib64 lib lib32 DOC "The file that corresponds to the il utility library.")

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${LIBPNG_INCLUDE_DIRS} ${IL_INCLUDE_DIRS})

target_link_libraries(untitled ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${LIBPNG_LIBRARIES} ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES})