cmake_minimum_required(VERSION 3.5)
project(Util)


set(SOURCE_FILES_RPN RPN.h RPN.cpp)
set(SOURCE_FILES_STACK Stack.h Stack.cpp)
set(SOURCE_FILES_LIST List.h List.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES_RPN} ${SOURCE_FILES_STACK} ${SOURCE_FILES_LIST})