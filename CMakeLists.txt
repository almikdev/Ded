cmake_minimum_required(VERSION 3.24)

project(MobileFrameCounter)

include(FetchContent)

# Позволяем Geode CLI автоматически управлять сборкой без find_package
add_geode_mod(
    my.framecounter
    VERSION 1.0.0
    SOURCES src/main.cpp
)
