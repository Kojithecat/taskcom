cmake_minimum_required(VERSION 3.10)
project(taskcom)

set(CMAKE_CXX_STANDARD 17)

add_executable(taskcom main.cpp)

# Add CLI11
include(FetchContent)
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(cli11)
target_link_libraries(taskcom CLI11::CLI11)

