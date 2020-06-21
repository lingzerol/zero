# CMakeList.txt: zeronet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("zeronet")

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src ZERO_LIB_SRCS)
message("${ZERO_LIB_SRCS}")

add_library(zero ${ZERO_LIB_SRCS})

add_executable(zeronet zeronet.cpp)

target_link_libraries(zeronet zero)