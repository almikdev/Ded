cmake_minimum_required(VERSION 3.24)

project(MobileFrameCounter)

# Принудительно подключаем Geode SDK через системные переменные GitHub Actions
if(NOT DEFINED GEODE_SDK AND DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK "$ENV{GEODE_SDK}" CACHE PATH "Path to Geode SDK")
endif()

list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}")

find_package(Geode REQUIRED)

add_geode_mod(
    my.framecounter
    VERSION 1.0.0
    SOURCES src/main.cpp
)
