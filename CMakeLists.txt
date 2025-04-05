cmake_minimum_required(VERSION 3.16)
project(ball_sim)

set(CMAKE_CXX_STANDARD 17)

# Find SFML using Homebrew installation path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add state header-only library
add_library(state-lib INTERFACE)
target_include_directories(state-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add ball simulation logic
add_library(ball-sim-lib
    BallSim.cc
    BallSim.hpp
    CollisionManager.hpp
    CollisionManager.cc
)
target_link_libraries(ball-sim-lib
    state-lib
    sfml-graphics
    sfml-window
    sfml-system
)
target_include_directories(ball-sim-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Build the executable
add_executable(ball-sim main.cc)
target_link_libraries(ball-sim ball-sim-lib)

