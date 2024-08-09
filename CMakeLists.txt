cmake_minimum_required(VERSION 3.22)
project(multithread-lab)

set(CMAKE_CXX_STANDARD 20)


add_library(
        thread_manager INTERFACE
)

add_library(
        file_manager INTERFACE
)

add_library(
        thread_safe_queue INTERFACE
)

target_include_directories(thread_manager INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(file_manager INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(thread_safe_queue INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Add PicoSHA2
add_subdirectory(external/PicoSHA2)

# Include the directory where PicoSHA2 is located
include_directories(external/PicoSHA2)

add_executable(cli cli/cli.cpp)
target_link_libraries(cli thread_manager)
target_link_libraries(cli file_manager)
target_link_libraries(cli thread_safe_queue)
