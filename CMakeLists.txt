cmake_minimum_required(VERSION 3.10.0)

project(Sudoku)

option(CLOUD OFF "Enable all sanitizers")
if(CLOUD)
    add_compile_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
    add_link_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
endif(CLOUD)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()

# Добавляем поддиректории
add_subdirectory(external/doctest)
add_subdirectory(src)




