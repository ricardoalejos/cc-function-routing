cmake_minimum_required(VERSION 3.16)
project(function_swap_demo C)

set(CMAKE_C_FLAGS " -Wall -Werror ")

add_library(application_regular OBJECT application.c)
add_library(application_patched OBJECT application.c)
target_compile_options(application_patched PRIVATE "-Dprintf=timestamped_printf")

add_library(timestamped_logger STATIC timestamped_logger.c)

add_executable(regular $<TARGET_OBJECTS:application_regular>)
add_executable(patched $<TARGET_OBJECTS:application_patched> timestamped_logger)
target_link_options(patched PRIVATE "-rdynamic")
