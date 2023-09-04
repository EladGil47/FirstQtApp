cmake_minimum_required(VERSION 3.5)

project(FirstQtApp VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Kohot)


# Determine the target architecture (32-bit or 64-bit)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET_ARCH "x64")  # 64-bit
else()
    set(TARGET_ARCH "x86")  # 32-bit
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        include/mainwindow.h
        QtFiles/mainwindow.ui
)

add_executable(FirstQtApp
        ${PROJECT_SOURCES})

link_directories(
    ${CMAKE_SOURCE_DIR}/Kohot)
 
target_link_libraries(FirstQtApp PRIVATE 
Qt6::Widgets
KOHOT_LIB
)
target_include_directories(FirstQtApp PUBLIC 
${CMAKE_SOURCE_DIR}/QtFiles
${CMAKE_SOURCE_DIR}/include
)

set_target_properties(FirstQtApp PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

# Adjust the build output directory based on the target architecture
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET_ARCH})

include(GNUInstallDirs)
install(TARGETS FirstQtApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
