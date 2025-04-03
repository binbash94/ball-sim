cmake_minimum_required(VERSION 3.16)
project(ball_sim)

set(CMAKE_CXX_STANDARD 17)

# Find SFML using Homebrew installation path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add library targets if needed
add_library(state-lib INTERFACE)
target_include_directories(state-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(ball-sim-lib
    ball-sim.cc
    ball-sim.hpp
)
target_link_libraries(ball-sim-lib state-lib sfml-graphics sfml-window sfml-system)
target_include_directories(ball-sim-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Final binary
add_executable(ball-sim main.cc)
target_link_libraries(ball-sim ball-sim-lib)
