cmake_minimum_required(VERSION 3.5)

project(crtp LANGUAGES CXX)
set(PROJECT_NAME crtp)
set (CMAKE_CXX_STANDARD 17)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/crtp)

add_executable(${PROJECT_NAME}
			   ${SOURCES_DIR}/crtp_example.cpp
)
			   
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCES_DIR})
