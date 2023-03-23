cmake_minimum_required(VERSION 2.8.12)

project(myadd)

include_directories(.)

add_library( ${PROJECT_NAME} myadd.cc)