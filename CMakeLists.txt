cmake_minimum_required(VERSION 3.2)

project(KohotQtApp VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Kohot)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

# Detect Qt 5 and Qt 6
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
if(TARGET Qt${QT_VERSION_MAJOR}::Widgets)
    message(STATUS "Qt found at: ${Qt${QT_VERSION_MAJOR}_DIR}")
endif()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    group_menu_window.cpp
    include/mainwindow.h
    include/group_menu_window.h

    base_list_manager_window.cpp
    include/base_list_manager_window.h

    group_item_widget.cpp
    include/group_item_widget.h

    player_item_widget.cpp
    include/player_item_widget.h

    include/custom_window.h

    include/editable_label.h
    editable_label.cpp

    include/app_common.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

link_directories(${CMAKE_SOURCE_DIR}/Kohot)

target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall
		)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    KOHOT_LIB
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
