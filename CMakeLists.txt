cmake_minimum_required(VERSION 3.2)
project(KohotQtApp VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(DEPS_LIBRARY KohotLibrary)
FetchContent_Declare(
	${DEPS_LIBRARY}
	GIT_REPOSITORY https://github.com/EladGil47/${DEPS_LIBRARY}.git
	GIT_TAG master
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/_deps/${DEPS_LIBRARY}
    BINARY_DIR ${PROJECT_SOURCE_DIR}/build/_deps/${DEPS_LIBRARY}
)
FetchContent_MakeAvailable(${DEPS_LIBRARY})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Detect Qt 5 and Qt 6
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
if(TARGET Qt${QT_VERSION_MAJOR}::Widgets)
    message(STATUS "Qt found at: ${Qt${QT_VERSION_MAJOR}_DIR}")
endif()

set(PROJECT_SOURCES
    main.cpp
    groups_list_window.cpp
    players_list_window.cpp
    base_list_manager_window.cpp
    group_item_widget.cpp
    player_item_widget.cpp
    editable_label.cpp
    windows_manager.cpp

    include/groups_list_window.h
    include/players_list_window.h
    include/base_list_manager_window.h
    include/group_item_widget.h
    include/player_item_widget.h
    include/editable_label.h
    include/windows_manager.h
    include/app_common.hpp

    include/create_teams_window.h
    include/base_player_item_widget.hpp
    include/checkable_player_item_widget.hpp
    include/display_teams_window.hpp
    include/labeled_list_widget.hpp
    include/team_player_item_widget.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

link_directories(${CMAKE_SOURCE_DIR}/${DEPS_LIBRARY})

target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall
		)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    KOHOT_LIB
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6Widgets_INCLUDE_DIRS}
)