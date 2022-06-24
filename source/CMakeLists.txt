cmake_minimum_required(VERSION 3.16)
project(function_swap_demo C)

set(CMAKE_C_FLAGS " -Wall -Werror ")

# Regular executable target with calls to printf()
add_executable(regular application.c)

# Application object with all references to printf() replaced with calls to
# timestamped_printf()
add_library(patched_application_object OBJECT application.c)
target_compile_options(patched_application_object PRIVATE "-Dprintf=timestamped_printf")

# Library with the implementation of timestamped_printf().
add_library(timestamped_logger STATIC timestamped_logger.c)

# Patched executable with calls to timestamped_printf()
add_executable(patched $<TARGET_OBJECTS:patched_application_object> timestamped_logger)
target_link_options(patched PRIVATE "-rdynamic")
