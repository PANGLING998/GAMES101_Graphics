cmake_minimum_required(VERSION 3.10)

project(Rasterizer)

aux_source_directory(src SRC_SUB)
aux_source_directory(. SRC_CUR)
set(OpenCV_DIR "C:\\threeparty\\opencv\\source\\opencv\\build\\x64\\mybuild")
set(LLIIBB "C:\\threeparty\\opencv\\source\\opencv\\build\\x64\\mybuild\\lib\\libopencv_gapi455.dll.a")
find_package(OpenCV REQUIRED)
include_directories("C:\\threeparty\\eigen3")
include_directories(include)
include_directories("C:\\threeparty\\opencv\\source\\opencv\\build\\x64\\mybuild\\include")
include_directories("C:\\threeparty\\opencv\\source\\opencv\\build\\include")

link_directories("C:\\threeparty\\opencv\\source\\opencv\\build\\x64\\vc15\\lib")
link_directories("C:/threeparty/opencv/source/opencv/build/x64/mybuild/lib")
set(CMAKE_CXX_STANDARD 17)
#message(STATUS "    version: ${OpenCV_VERSION}")
#message(STATUS "    libraries: ${OpenCV_LIBS}")
#message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(raster ${SRC_SUB} ${SRC_CUR})
message(STATUS "    lllllllllll path: ${OpenCV_LIBRARIES}")
target_link_libraries(raster ${OpenCV_LIBRARIES})

