cmake_minimum_required(VERSION 2.8)

project( mahal_finder )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
find_package( OpenCV REQUIRED )

link_directories( "../libmahalfind/lib" )
include_directories( ${OpenCV_INCLUDE_DIRS} "./")

add_executable( object_finder src/object_finder_main.cpp )
target_link_libraries( object_finder ${OpenCV_LIBS} "libmahalfind.so" )



