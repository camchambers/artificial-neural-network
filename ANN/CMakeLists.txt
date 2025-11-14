# CMakeLists.txt : CMake project for ArtificialNeuralNetwork, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("ArtificialNeuralNetwork")

include_directories(${PROJECT_SOURCE_DIR})

# Add source to this project's executable.
add_executable (
ArtificialNeuralNetwork
"Main.cpp"
"ArtificialNeuralNetwork.cpp" 
"ArtificialNeuralNetwork.h"
"Layer.cpp"
"Layer.h"
"Neuron.cpp"
"Neuron.h"
"Connection.cpp" 
"Connection.h"
"TrainingSet.cpp"
"TrainingSet.h"
)


set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ann")
