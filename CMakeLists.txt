cmake_minimum_required(VERSION 3.10)
project(NodevisionDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to build the standalone executable (for local testing)
option(BUILD_EXECUTABLE "Build the standalone executable for local testing" OFF)

# Include your project's headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define preprocessor macro for Node-API
add_definitions(-DNAPI_VERSION=4)

# Manually include node-addon-api
include_directories(${CMAKE_SOURCE_DIR}/node_modules/node-addon-api)

# === Node-API module target (to be published as the npm package) ===
# This target builds your Node.js addon. Use binding.cpp which contains the Node-API registration.
add_library(nodevision_db SHARED 
    src/binding.cpp
    src/GraphDB.cpp
)
target_include_directories(nodevision_db PRIVATE ${CMAKE_JS_INC} ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api)
target_link_libraries(nodevision_db PRIVATE ${CMAKE_JS_LIB})
set_target_properties(nodevision_db PROPERTIES PREFIX "" SUFFIX ".node")

# === Optionally build the standalone executable (for local testing) ===
if(BUILD_EXECUTABLE)
    add_executable(nodevision_db_executable
        src/main.cpp
        src/GraphDB.cpp
    )
    # For the executable, we need the Node.js headers too.
    target_include_directories(nodevision_db_executable PRIVATE ${CMAKE_JS_INC} ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api)
endif()

# === Enable Testing ===
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
add_test(NAME RunTests COMMAND test_runner)
