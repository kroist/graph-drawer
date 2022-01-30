cmake_minimum_required(VERSION 3.16)
project(GraphDrawer)
set (CMAKE_CXX_STANDARD 11)

add_executable(drawer shared.cpp graphIO.cpp main.cpp algo.cpp planar.cpp)


include(FetchContent)

# JSON
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  message(STATUS "Fetching 'JSON for Modern C++' library")
  FetchContent_Populate(json)
  message(STATUS "Fetching finished")

  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# GFLAGS
FetchContent_Declare(gflags
  GIT_REPOSITORY https://github.com/gflags/gflags.git
  GIT_TAG v2.2.2)

FetchContent_GetProperties(gflags)
if(NOT gflags_POPULATED)
  message(STATUS "Fetching gflags library")
  FetchContent_Populate(gflags)
  message(STATUS "Fetching finished")
  add_subdirectory(${gflags_SOURCE_DIR} ${gflags_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


target_link_libraries(drawer PRIVATE nlohmann_json::nlohmann_json gflags)

# OPENMP
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

message(STATUS "Fetching Catch2 library")
FetchContent_MakeAvailable(Catch2)
message(STATUS "Fetching finished")

file(GLOB tests_SRC CONFIGURE_DEPENDS "test/*.cpp")

set(TEST_FILES shared.h shared.cpp graphIO.h graphIO.cpp)

add_executable(tests ${tests_SRC} ${TEST_FILES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(drawer PRIVATE nlohmann_json::nlohmann_json gflags)

# LEMON
include(ExternalProject)
ExternalProject_Add(
        lemon
        PREFIX     external
        URL        http://lemon.cs.elte.hu/pub/sources/lemon-1.3.1.tar.gz
        URL_HASH   MD5=e89f887559113b68657eca67cf3329b5
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=lemon
        UPDATE_DISCONNECTED ${OFFLINE}
)

set(LIBLEMON_ROOT ${CMAKE_CURRENT_BINARY_DIR}/external/src/lemon-build/lemon/)

include_directories(
  "${LIBLEMON_ROOT}/include"
)
link_directories( "${LIBLEMON_ROOT}/lib")
add_dependencies(drawer lemon)
