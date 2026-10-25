cmake_minimum_required(VERSION 3.24)

# Автоматически подключаем окружение Geode, если оно установлено в системе
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

project(MobileFrameCounter)

find_package(Geode REQUIRED)

add_geode_mod(
    my.framecounter
    VERSION 1.0.0
    SOURCES src/main.cpp
)
