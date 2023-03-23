cmake_minimum_required(VERSION 2.8.12)

project(addon)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(STATUS "operation system is ${CMAKE_SYSTEM}")

add_definitions(-std=c++11)
#add_compile_options(-g)

# 设置头文件路径
include_directories(${CMAKE_JS_INC})
include_directories(.)

# thirdlib
include_directories(thirdlib)  
add_subdirectory(thirdlib)

# 源文件列表
file(GLOB SOURCE_FILES addon.cpp)

# 生成.node文件
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

# 设置输出文件后缀
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# 设置库依赖
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} myadd)
