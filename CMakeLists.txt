cmake_minimum_required(VERSION 3.16)
project(GraphDrawer)

add_executable(drawer shared.cpp graphIO.cpp main.cpp algo.cpp)


include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_subdirectory(submodules/gflags)

target_link_libraries(drawer PRIVATE nlohmann_json::nlohmann_json gflags)

find_package(OpenMP)

if (OpenMP_CXX_FOUND)
    target_link_libraries(drawer PRIVATE OpenMP::OpenMP_CXX)
endif()


