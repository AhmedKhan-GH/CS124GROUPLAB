cmake_minimum_required(VERSION 3.5)
project(main)

# Find X11 library
find_package(X11 REQUIRED)

# Add executable
add_executable(main main.cpp)

# Link against X11 library
target_link_libraries(main ${X11_LIBRARIES})

