# *** Application ***

cmake_minimum_required(VERSION 3.5)
project(ichaika_rest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE Release)

set(SRC src/LRUCache.hpp)

add_executable(${PROJECT_NAME} ${SRC} src/main.cpp)

find_package(Drogon CONFIG REQUIRED PATHS /usr/local/lib64/cmake/Drogon)

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# *** Unit tests ***
find_package(GTest REQUIRED)

enable_testing()

set(PROJECT_NAME_TEST test_${PROJECT_NAME} )

add_executable(${PROJECT_NAME_TEST} ${SRC} test/LRUCacheTest.cpp)

target_link_libraries(${PROJECT_NAME_TEST} Drogon::Drogon gtest gtest_main)
target_include_directories(${PROJECT_NAME_TEST} PRIVATE src)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME_TEST})
