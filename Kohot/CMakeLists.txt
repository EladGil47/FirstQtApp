CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(Kohot VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(KOHOT_LIB  
src/base_collection.cpp
src/group.cpp
src/groups_collection.cpp  
src/json_utils.cpp  
src/kohot.cpp  
src/player.cpp  
src/players_collection.cpp  
src/players_sorter.cpp  
src/team.cpp  
src/teams_creator.cpp  
src/utility_functions.cpp  
include/base_collection.hpp  
include/console_colors.hpp  
include/group.hpp  
include/groups_collection.hpp  
include/json_utils.hpp  
include/kohot.hpp  
include/player.hpp  
include/players_collection.hpp  
include/players_sorter.hpp  
include/team.hpp  
include/teams_creator.hpp  
include/utility_functions.hpp
)

target_include_directories(KOHOT_LIB PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


# SET(CREATE_CONSOLE_APP true)
# if(${CREATE_CONSOLE_APP})

# set(CONSOLE_APP_KOHOT_LIB_SOURCES
# src/menu.cpp  
# src/group_menu.cpp 
# src/final_menu.cpp
# src/groups_manager_menu.cpp  
# src/players_menu.cpp  
# include/groups_manager_menu.hpp  
# include/group_menu.hpp  
# include/final_menu.hpp  
# include/menu.hpp  
# include/players_menu.hpp  
# include/user_interaction.hpp  
# )
# add_executable(ConsoleAppKohot ${CONSOLE_APP_KOHOT_LIB_SOURCES})

# target_include_directories(ConsoleAppKohot PUBLIC
#     ${PROJECT_SOURCE_DIR}/include
# )

# target_link_libraries(ConsoleAppKohot PRIVATE
# KOHOT_LIB
# )

# endif()