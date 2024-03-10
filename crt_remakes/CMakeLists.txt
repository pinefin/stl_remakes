cmake_minimum_required(VERSION 3.16)
add_library(crt_remakes INTERFACE)

target_include_directories(crt_remakes
    INTERFACE
        .
)

target_sources(crt_remakes
    INTERFACE
        crt_remakes.cpp
)
