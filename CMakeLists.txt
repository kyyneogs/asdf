cmake_minimum_required(VERSION 3.20.0)
project(asdf VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(EXPORT_COMPILE_COMMANDS ON)

find_package(Boost CONFIG)

include_directories(src)
add_compile_options(/utf-8)
file(GLOB SRC src/asdf/*.cpp src/asdf/*.cc)

add_executable(asdf main.cpp ${SRC})
target_include_directories(asdf PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(asdf PRIVATE -DASDF_USE_ABORT -DASDF_USE_PRETTY_PRINT)
# add_executable(test main.cpp)

