cmake_minimum_required (VERSION 2.8)

# About the project
# ------------------------
# Project name
project(klust)


# Options
# ------------------------
# Change default install path
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/bin" CACHE PATH "default install path" FORCE)
endif()

if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()


# Compiler options
# ------------------------
# Thanks to Will Usher for this code snippet:
# http://www.willusher.io/sdl2%20tutorials/2014/03/06/lesson-0-cmake/
#
# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -Werror -pedantic-errors -std=c++11")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()


# Set up BioIO so it downloads and compiles automatically
# ------------------------
include(ExternalProject)
set(bioio_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/bioio")
set(bioio_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/bioio")
set(bioio_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${bioio_INSTALL_DIR})
ExternalProject_Add(
	bioio
	PREFIX ${bioio_PREFIX}
	GIT_REPOSITORY https://github.com/BIO-DIKU/BioIO.git
	GIT_TAG develop
	INSTALL_DIR ${bioio_INSTALL_DIR}
	CMAKE_ARGS ${bioio_CMAKE_ARGS}
)

# Link BioIO
include_directories(${bioio_INSTALL_DIR}/include)
link_libraries(${bioio_INSTALL_DIR}/lib/libBioIO.a)


# Executable
# ------------------------
FILE(GLOB SOURCE_FILES src/*.cc src/modules/*.cc)
FILE(GLOB HEADER_FILES src/*.h src/modules/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})


# Build tests if CMAKE_BUILD_TYPE=Debug is set
# ------------------------
if (CMAKE_BUILD_TYPE MATCHES DEBUG OR CMAKE_BUILD_TYPE MATCHES "Debug")
    include_directories(${BIOIO_INCLUDE_DIR})
    FILE(GLOB TEST_FILES test/*.cc test/modules/*.cc)
    add_executable("${PROJECT_NAME}-test" ${TEST_FILES})
    target_link_libraries("${PROJECT_NAME}-test")
endif()
