cmake_minimum_required(VERSION 3.20)
project(untitled1)

#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
set(-D_GLIBCXX_USE_CXX11_ABI 0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${PROJECT_SOURCE_DIR}/include)

#list(APPEND SOURCES
#        main.cpp
#        /home/chenyl/Downloads/package/samples/_libs/xiAPIplusOpenCV/xiApiPlusOcv
#        )

include_directories(/home/chenyl/Downloads/package/samples/_libs)

include(/home/chenyl/Downloads/package/samples/_libs/_cmake/add_xiapi.cmake)
include(/home/chenyl/Downloads/package/samples/_libs/_cmake/add_opencv.cmake)
#include(/home/chenyl/Downloads/package/samples/_libs/_cmake/add_executable.cmake)


file(GLOB SOURCE_FILES *.cpp)

#add_executable(untitled1 test_yolo.cpp)
add_executable(untitled1 main.cpp detector.cpp)
#add_executable(untitled1 version.cpp)
#add_executable(untitled1 testfile.cpp)
#add_executable(untitled1 test_cam.cpp detector.cpp include/xiApiPlusOcv.cpp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=1")
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
#set(OPENCV_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1")
set(OpenCV_DIR "/home/chenyl/opencv/build")
#set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")


find_package(OpenCV 4 REQUIRED)


message(STATUS "OpenCV library status:")
message(STATUS "    version:${OpenCV_VERSION}")
message(STATUS "    libraries:${OpenCV_LIBS}")
message(STATUS "    include path:${OpenCV_INCLUDE_DIRS}")
message(STATUS "    OpenCV_DIR:${OpenCV_DIR}")
#message(STATUS "    OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})




set(CMAKE_PREFIX_PATH  /home/chenyl/Downloads/libtorch-cxx11-abi-shared-with-deps-1.10.0+cu113/libtorch)
find_package(Torch REQUIRED)
find_package(Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

target_link_libraries(untitled1 ${OpenCV_LIBS})
target_link_libraries(untitled1 "${TORCH_LIBRARIES}")
target_link_libraries(untitled1 ${CMAKE_THREAD_LIBS_INIT})


