cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0074 NEW)

project(cpp-tricks LANGUAGES CXX)
set(PROJECT_NAME cpp-tricks)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(${SOURCES_DIR}/crtp)
add_subdirectory(${SOURCES_DIR}/simple_threadpool)
add_subdirectory(${SOURCES_DIR}/cache_invalidation)