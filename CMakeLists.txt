cmake_minimum_required(VERSION 3.1)

project(main)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable(main
    main.cpp
)

target_link_libraries(main
    ${wxWidgets_LIBRARIES}
)
