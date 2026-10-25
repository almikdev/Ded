cmake_minimum_required(VERSION 3.24)

project(MobileFrameCounter)

find_package(Geode REQUIRED)

add_geode_mod(
    my.framecounter
    VERSION 1.0.0
    SOURCES src/main.cpp
)

