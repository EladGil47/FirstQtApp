cmake_minimum_required(VERSION 3.2)
project(KohotQtApp VERSION 1.0.0 LANGUAGES CXX)
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

file(GLOB PROJECT_SOURCES
    *.cpp
    include/*.h
    include/*.hpp
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

# CPACK SECTION 
# Set the CPack variables
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_GENERATOR "ZIP")  # Use ZIP generator for standalone package

# Include the CPack module
include(CPack)

# Include the necessary files in the package
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Include the Data Dir
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Data"
    DESTINATION .
    FILES_MATCHING PATTERN "*.*"
)