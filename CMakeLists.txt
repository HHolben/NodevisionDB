cmake_minimum_required(VERSION 3.10)
project(NodevisionDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable target
add_executable(nodevision_db
    src/main.cpp
    src/GraphDB.cpp
)

# Enable testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable target
add_executable(test_runner
    test/test_graphdb.cpp
    src/GraphDB.cpp
)
target_link_libraries(test_runner
    GTest::GTest
    GTest::Main
    pthread
)

# Register the test with CTest
add_test(NAME RunTests COMMAND test_runner)
