cmake_minimum_required(VERSION 3.2)
project(KohotQtApp VERSION 1.1.0 LANGUAGES CXX)
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
    src/*.cpp
    include/*.h
    include/*.hpp
)

qt_add_resources(RESOURCES resources.qrc)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${RESOURCES})

link_directories(${CMAKE_SOURCE_DIR}/${DEPS_LIBRARY})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui 

    KOHOT_LIB
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6Widgets_INCLUDE_DIRS}
)


# CPACK SECTION
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGING_INSTALL_PREFIX ".")
    message("System : Windows")

endif()

if(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "eladgil47@gmail.com")
    set(CPACK_PACKAGING_INSTALL_PREFIX "$ENV{HOME}/Downloads/${PROJECT_NAME}")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5widgets5")
    message("System : Linux")
endif()
message("-- Notice : Application path: ${CPACK_PACKAGING_INSTALL_PREFIX}")


include(CPack)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CPACK_PACKAGING_INSTALL_PREFIX})

install(DIRECTORY "${PROJECT_SOURCE_DIR}/Data"
    DESTINATION ${CPACK_PACKAGING_INSTALL_PREFIX}
    FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE
    DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
    FILES_MATCHING PATTERN "*.*"
)