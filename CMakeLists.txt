cmake_minimum_required(VERSION 3.16)
project(GraphDrawer)

add_executable(drawer shared.cpp graphIO.cpp main.cpp algo.cpp)


include(FetchContent)

# JSON

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# GFLAGS

FetchContent_Declare(gflags
  GIT_REPOSITORY https://github.com/gflags/gflags.git
  GIT_TAG v2.2.2)

FetchContent_GetProperties(gflags)
if(NOT gflags_POPULATED)
  FetchContent_Populate(gflags)
  add_subdirectory(${gflags_SOURCE_DIR} ${gflags_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()



target_link_libraries(drawer PRIVATE nlohmann_json::nlohmann_json gflags)

find_package(OpenMP)

if (OpenMP_CXX_FOUND)
    target_link_libraries(drawer PRIVATE OpenMP::OpenMP_CXX)
endif()

# TESTING
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)


file(GLOB tests_SRC CONFIGURE_DEPENDS "test/*.cpp")

add_executable(tests ${tests_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
