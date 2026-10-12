cmake_minimum_required(VERSION 3.12)

project(05.homework)

add_executable(main
    main.cpp
    MyContainers.h
)

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)