cmake_minimum_required(VERSION 3.11)

if(WIN32)
  set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
      CACHE STRING "")
  set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET} CACHE STRING "")
endif()

project(hvr-log LANGUAGES CXX)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(MSVC)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP /WX /sdl")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127") # condition is constant
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44062")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44191")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44242")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44254")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44255")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44263")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44264")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44265")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44266")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44287")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44289")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44296")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44302")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44311")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44339")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44342")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44350")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44355")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44370")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44371")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44388")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44412")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44431")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44435")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44437")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44444")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44471")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44472")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44536")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44545")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44546")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44547")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44548")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44555")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44557")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44574")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44628")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44640")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44682")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44686")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44692")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44738")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44786")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44826")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44837")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44905")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44906")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44917")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44928")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44931")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44946")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44962")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44986")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44987")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44988")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX
       OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fsigned-char -Wshadow")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wpedantic -Wcast-qual")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Winline")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

set(CLANG_TIDY_EXECUTABLE "clang-tidy" CACHE STRING "clang-tidy")
set(CLANG_TIDY_FLAGS "-checks=-*,modernize-*,mpi-*,performance-*,readability-*")
string(APPEND CLANG_TIDY_FLAGS ",-readability-avoid-const-params-in-decls")

option(RUN_CLANG_TIDY "run clang tidy during compilation" ON)

if(RUN_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};${CLANG_TIDY_FLAGS};-fix")
else()
  set(CMAKE_CXX_CLANG_TIDY "")
endif()

set(CPPLINT_EXECUTABLE "cpplint" CACHE STRING "cpplint")

option(RUN_CPPLINT "run cpplint during compilation" ON)

if(RUN_CPPLINT)
  set(CMAKE_CXX_CPPLINT "${CPPLINT_EXECUTABLE};--quiet")
else()
  set(CMAKE_CXX_CPPLINT "")
endif()

if(NOT TARGET uninstall)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake IMMEDIATE @ONLY)

  add_custom_target(
    uninstall COMMAND ${CMAKE_COMMAND} -P
                      ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  export(TARGETS FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)
endif()

file(WRITE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
     "include(CMakeFindDependencyMacro)\n"
     "include(\${CMAKE_CURRENT_LIST_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)\n")

add_subdirectory(modules)

option(BUILD_APPS "Build apps" ON)

if(BUILD_APPS)
  add_subdirectory(apps)
endif()

option(BUILD_DOCS "Build docs" ON)

if(BUILD_DOCS)
  add_subdirectory(doc)
endif()

option(BUILD_UNIT_TEST "Build unit tests" ON)

if(BUILD_UNIT_TEST)
  add_subdirectory(unit-test)
endif()

install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

install(EXPORT ${CMAKE_PROJECT_NAME}Targets NAMESPACE hvr::
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

if(NOT TARGET install-app)
  add_custom_target(
    install-app
    COMMAND "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=install-app -P
            "${CMAKE_BINARY_DIR}/cmake_install.cmake")
endif()

file(GLOB_RECURSE SRC_FILES modules/*.cpp modules/*.h modules/*.cu
     modules/*.cuh apps/*.cpp apps/*.h unit-test/*cpp unit-test/*.h)
file(GLOB_RECURSE CMAKE_FILES modules/*CMakeLists.txt apps/*CMakeLists.txt
     unit-test/*CMakeLists.txt)
list(APPEND CMAKE_FILES ${CMAKE_SOURCE_DIR}/CMakeLists.txt)

set(CLANG_FORMAT_EXECUTABLE "clang-format" CACHE STRING "clang-format")
set(CMAKE_FORMAT_EXECUTABLE "cmake-format" CACHE STRING "cmake-format")

add_custom_target(
  format COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${SRC_FILES}
  COMMAND ${CMAKE_FORMAT_EXECUTABLE} --max-pargs-hwrap 10 --max-subgroups-hwrap
          10 -i ${CMAKE_FILES})
