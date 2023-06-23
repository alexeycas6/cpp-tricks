cmake_minimum_required(VERSION 3.5)

project(cache_invalidation LANGUAGES CXX)
set(PROJECT_NAME cache_invalidation)
set (CMAKE_CXX_STANDARD 20)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/cache_invalidation)

add_executable(${PROJECT_NAME}
			   ${SOURCES_DIR}/cache_invalidation.hpp
			   ${SOURCES_DIR}/cache_invalidation_example.cpp
)
			   
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCES_DIR})
