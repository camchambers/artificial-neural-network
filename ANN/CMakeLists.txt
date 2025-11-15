# CMakeLists.txt : CMake project for ArtificialNeuralNetwork, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.10)
project(ArtificialNeuralNetwork VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (explicitly listed - better than GLOB)
set(ANN_SOURCES
    ArtificialNeuralNetwork.cpp
    Layer.cpp
    Neuron.cpp
    Connection.cpp
    TrainingSet.cpp
)

# Main executable
add_executable(ann Main.cpp ${ANN_SOURCES})

# Enable testing
enable_testing()

# Test executable
add_executable(test_ann 
    tests/test_ann.cpp
    ${ANN_SOURCES}
)

# Add test to CTest
add_test(NAME ANN_Unit_Tests COMMAND test_ann)

# Optional: Set output directories
set_target_properties(ann test_ann PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print configuration info
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
