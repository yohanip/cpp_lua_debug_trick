cmake_minimum_required(VERSION 3.28)

project(TestExecutable CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(prog main.cpp)

target_include_directories(prog PRIVATE 
    ../c/lua
)

target_link_libraries(prog raylib_lua lua)

target_link_directories(prog PRIVATE 
    ../install/lib
    ../c/install/linux/Debug/lib
)

install(TARGETS prog)