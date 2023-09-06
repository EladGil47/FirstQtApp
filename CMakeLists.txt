cmake_minimum_required(VERSION 3.5)

project(KohotQtApp VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Kohot)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    include/mainwindow.h
    include/group_menu_window.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

link_directories(${CMAKE_SOURCE_DIR}/Kohot)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    KOHOT_LIB
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)