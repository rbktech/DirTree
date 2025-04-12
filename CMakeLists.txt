cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(DirTree VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

add_definitions(-DNDEBUG)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O2)
endif()

add_compile_options(-Wall)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_link_options(-s)
endif()

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME dirt-${CMAKE_BUILD_TYPE}-${PROJECT_VERSION}
)

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/arg.cpp)