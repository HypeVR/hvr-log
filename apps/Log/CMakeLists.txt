cmake_minimum_required(VERSION 3.7)
project(glog_sample)

set(PROJECT_SRCS
#${PROJECT_SOURCE_DIR}/src/SampleExample.cpp
${PROJECT_SOURCE_DIR}/src/glog_sample.cpp
)
find_package(glog)

source_group("src" FILES ${PROJECT_SRCS})

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

target_link_libraries(${PROJECT_NAME} hvr_log glog::glog)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${CMAKE_PROJECT_NAME}/apps)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        DESTINATION bin)
