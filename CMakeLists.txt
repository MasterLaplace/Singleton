# Singleton/CMakeLists.txt
cmake_minimum_required(VERSION 3.2...3.22)

project(Singleton VERSION 1.0.2 LANGUAGES CXX)

include(FetchContent)

set(MAIN_PROJECT OFF)

if (CMAKE_C_COMPILER)
    set(HEADERS
        singleton_config.h
        singleton.h
    )
else()
    set(HEADERS
        singleton_config.h
        Singleton.hpp
    )
endif()

install(FILES ${HEADERS} DESTINATION include)
add_library(Singleton INTERFACE)
target_include_directories(Singleton INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
