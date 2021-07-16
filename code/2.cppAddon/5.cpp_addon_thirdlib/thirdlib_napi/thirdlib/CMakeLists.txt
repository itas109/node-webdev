cmake_minimum_required(VERSION 2.8)

project(myadd)

message(STATUS "operation system is ${CMAKE_SYSTEM}")

#add_compile_options(-g)

# 设置头文件路径
# include_directories(~/.cache/node-gyp/12.13.0/include/node)
include_directories(.)

# 设置依赖文件路径
# link_directories(.)

# 源文件列表
file(GLOB_RECURSE SOURCE_CPP myadd.cc) 

# 生成库文件
add_library( ${PROJECT_NAME} SHARED ${SOURCE_CPP})

# 设置输出文件后缀
#set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
# 设置输出文件后缀
#set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .node)