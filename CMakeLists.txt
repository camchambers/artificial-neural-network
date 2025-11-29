cmake_minimum_required(VERSION 3.10)
project(ANN VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print configuration info
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# Source files for the library
set(ANN_SOURCES
    src/ArtificialNeuralNetwork.cpp
    src/Layer.cpp
    src/Neuron.cpp
    src/Connection.cpp
    src/TrainingSet.cpp
)

# Create the ANN library
add_library(ann ${ANN_SOURCES})

# Set include directories for the library
target_include_directories(ann
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Optional: Build examples
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    message(STATUS "Building examples")
    
    # XOR classification example
    add_executable(xor_classification examples/xor_classification.cpp)
    target_link_libraries(xor_classification PRIVATE ann)
    
    # Copy training data to build directory
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/train.csv
        ${CMAKE_CURRENT_BINARY_DIR}/train.csv
        COPYONLY
    )
endif()

# Optional: Build tests
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    message(STATUS "Building tests")
    
    # Test executable
    add_executable(test_ann 
        tests/test_ann.cpp
    )
    
    target_link_libraries(test_ann PRIVATE ann)
    
    # Add test to CTest
    add_test(NAME ANN_Unit_Tests COMMAND test_ann)
endif()

# Installation rules
install(TARGETS ann
    EXPORT ANNTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
)

install(EXPORT ANNTargets
    FILE ANNConfig.cmake
    NAMESPACE ann::
    DESTINATION lib/cmake/ANN
)

# Create version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ANNConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ANNConfigVersion.cmake"
    DESTINATION lib/cmake/ANN
)
