cmake_minimum_required(VERSION 3.23)
project(Gluttonous_Snake)

set(CMAKE_CXX_STANDARD 14)
set(EasyX_DIR D:/Offware/easyx4mingw_20220901)

include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)
link_libraries(libeasyx.a)
add_executable(Gluttonous_Snake main.cpp)
