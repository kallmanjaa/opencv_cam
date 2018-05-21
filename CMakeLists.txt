cmake_minimum_required(VERSION 3.10)

set(prog face_detect)
find_package( OpenCV REQUIRED )
add_library(${prog} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/${prog}.cpp)
target_link_libraries (${prog} ${OpenCV_LIBS})
target_include_directories (${prog} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(prog facedetect_demo)
add_executable( ${prog} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )
target_link_libraries (${prog} face_detect pthread)
target_include_directories (${prog} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)