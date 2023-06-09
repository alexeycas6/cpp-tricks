cmake_minimum_required(VERSION 3.5)

project(thread_pool LANGUAGES CXX)
set(PROJECT_NAME thread_pool)
set (CMAKE_CXX_STANDARD 17)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/simple_threadpool)

add_executable(${PROJECT_NAME}
			   ${SOURCES_DIR}/thread_pool.hpp
			   ${SOURCES_DIR}/thread_pool_example.cpp
)
			   
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCES_DIR})
