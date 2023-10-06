# Minimum version of CMake required
cmake_minimum_required(VERSION 3.0)

# Project name
project(MyCProject)

# Specify the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Specify the include directory
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Specify the output directory for object files
set(OBJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/obj)

# Add all source files in the 'src' directory to the project
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Include the 'inc' directory for header files
include_directories(${INC_DIR})

# Create the executable from 'main.c' and other source files
add_executable(my_app ${SRC_FILES} main.c)

# Set the output directory for the executable
set_target_properties(my_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OBJ_DIR}
)

# Custom target for running the application
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/obj/my_app
    DEPENDS my_app
    WORKING_DIRECTORY ${OBJ_DIR}
    COMMENT "Running my_app"
)

# Custom target for debugging with GDB
add_custom_target(debug_gdb
    COMMAND gdb ${OBJ_DIR}/my_app
    DEPENDS my_app
    WORKING_DIRECTORY ${OBJ_DIR}
    COMMENT "Debugging my_app with GDB"
)

# Custom target for debugging with Valgrind (memory leak check)
add_custom_target(debug_mem
    COMMAND valgrind --leak-check=full ${OBJ_DIR}/my_app
    DEPENDS my_app
    WORKING_DIRECTORY ${OBJ_DIR}
    COMMENT "Debugging my_app with Valgrind for memory leaks"
)
