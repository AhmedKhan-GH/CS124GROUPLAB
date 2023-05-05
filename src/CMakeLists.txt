cmake_minimum_required(VERSION 3.5)
project(main)

# Set the source files to be built
set(SOURCE_FILES
    Runtime.cpp
    main.cpp
    Wayspace.cpp
    FileManager.cpp
)

# Create an executable target
add_executable(main ${SOURCE_FILES})

