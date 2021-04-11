cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(HOMEWORK_1)

add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/overall_plan.cpp
        sources/db_driver.cpp
        sources/individual_plan.cpp
        )

add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(demo ${PROJECT_NAME})