cmake_minimum_required(VERSION 3.7)
project(LogTest)

set(LOG_INCS
${PROJECT_SOURCE_DIR}/include/LogTest.h
)

set(LOG_SRCS
${PROJECT_SOURCE_DIR}/src/LogTest.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
  add_definitions("-DBOOST_ALL_NO_LIB")
endif()

find_package( Boost COMPONENTS system filesystem regex REQUIRED )

add_executable(LogTest ${LOG_SRCS} ${LOG_INCS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
                            HVR_WINDOWS_DISABLE_ALL_WARNING=${DISABLE}
                            HVR_WINDOWS_ENABLE_ALL_WARNING=${ENABLE})

target_include_directories(${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(LogTest hvr_log ${Boost_LIBRARIES} gtest_main)

set_property(TARGET LogTest PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/unit-test)
