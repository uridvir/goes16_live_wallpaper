# IMPORTANT: For this build system to work properly, you need to download DownloadProject yourself from the repo at
# https://github.com/Crascit/DownloadProject. Place DownloadProject.cmake and DownloadProject.CMakeLists.cmake.in into
# the root of the project (none of the other files in the repo are needed). Also make sure CMake is installed on your
# system, and if you're confused, consult the Internet on how to use it. It is remarkably easy to use, hence why I
# chose it as the build system for this project.

# You must build this project with version 3.2 or higher of CMake, because I don't feel like supporting older versions.
cmake_minimum_required(VERSION 3.2)

project(goes16_live_wallpaper)

include(CTest)
include(DownloadProject.cmake)
include(ExternalProject)

set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Downloads googletest and sets it up
download_project(
  PROJ                  googletest
  GIT_REPOSITORY        https://github.com/google/googletest.git
  GIT_TAG               master
  UPDATE_DISCONNECTED   1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

# Downloads json library and sets it up
download_project(
  PROJ                  json
  GIT_REPOSITORY        https://github.com/nlohmann/json.git
  GIT_TAG               master
  UPDATE_DISCONNECTED   1
)
add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})

# Downloads curl and sets it up
download_project(
  PROJ                  curl
  GIT_REPOSITORY        https://github.com/curl/curl.git
  GIT_TAG               master
  UPDATE_DISCONNECTED   1
)
add_subdirectory(${curl_SOURCE_DIR} ${curl_BINARY_DIR})

# Downloads lodepng and sets it up
execute_process(COMMAND git clone https://github.com/lvandeve/lodepng.git WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Add header files to include list
set(
  HEADER_LIST
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_BINARY_DIR}/lodepng"
  "${googletest_SOURCE_DIR}/include"
  "${curl_SOURCE_DIR}/include"
  "${json_SOURCE_DIR}/src"
)

# Add source code to build system
add_subdirectory(src)

# Copy compile_commands.json to root directory
# if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
#   configure_file("${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}/compile_commands.json" COPYONLY)
# endif(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
