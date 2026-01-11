cmake_minimum_required(VERSION 3.28)

project(RaylibLuaModule CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_RPATH $ORIGIN)
set(CMAKE_INSTALL_RPATH $ORIGIN)
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(raylib_lua SHARED src/lib.cpp)

target_include_directories(raylib_lua PRIVATE
    c/lua
    c/raylib/src
)

target_link_libraries(raylib_lua raylib lua)
target_link_directories(raylib_lua PRIVATE 
    c/install/linux/Debug/lib
)

install(TARGETS raylib_lua)