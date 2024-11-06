# Singleton/CMakeLists.txt
cmake_minimum_required(VERSION 3.2...3.22)

project(R-Type_Server VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)

set(MAIN_PROJECT OFF)

if (CMAKE_C_COMPILER)
    set(HEADERS
        config.h
        singleton.h
    )
else()
    set(HEADERS
        config.h
        Singleton.hpp
    )
endif()

add_library(singleton_lib STATIC ${HEADERS})
target_include_directories(singleton_lib PUBLIC "${PROJECT_SOURCE_DIR}")

if (MAIN_PROJECT)
    install(TARGETS singleton_lib DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include)
endif()
