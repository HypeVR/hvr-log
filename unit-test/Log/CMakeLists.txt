cmake_minimum_required(VERSION 3.11)

project(LogTest)

set(LOG_INCS ${PROJECT_SOURCE_DIR}/include/LogTest.h)

set(LOG_SRCS ${PROJECT_SOURCE_DIR}/src/LogTest.cpp
             ${PROJECT_SOURCE_DIR}/src/main.cpp)

find_package(GTest CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

add_executable(LogTest ${LOG_SRCS} ${LOG_INCS})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_link_libraries(LogTest hvr_log Boost::filesystem GTest::gtest_main)

set_property(TARGET LogTest PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/unit-test)
