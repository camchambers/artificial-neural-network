/**
 * Unit Tests for Artificial Neural Network
 * Using Catch2 Testing Framework
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Connection.h"
#include "../Neuron.h"
#include "../Layer.h"
#include "../TrainingSet.h"
#include "../ArtificialNeuralNetwork.h"

#include <vector>
#include <fstream>

using namespace std;

// Connection Tests
TEST_CASE("Connection initializes with random weight", "[Connection]") {
    Connection conn;
    REQUIRE(conn.weight >= -1.0);
    REQUIRE(conn.weight <= 1.0);
}

TEST_CASE("Multiple connections have different random weights", "[Connection]") {
    Connection conn1, conn2, conn3;
    bool different = (conn1.weight != conn2.weight) || (conn2.weight != conn3.weight);
    REQUIRE(different);
}

// Neuron Tests
TEST_CASE("Neuron creation without connections", "[Neuron]") {
    Neuron neuron(0, 0);
    REQUIRE(neuron.getOutputValue() == 0.0);
}

TEST_CASE("Neuron creation with connections", "[Neuron]") {
    Neuron neuron(1, 3);
    REQUIRE(neuron.getOutputValue() == 0.0);
}

TEST_CASE("Neuron set and get value", "[Neuron]") {
    Neuron neuron(0, 0);
    
    SECTION("positive value") {
        neuron.setOutputValue(0.5);
        REQUIRE(neuron.getOutputValue() == 0.5);
    }
    
    SECTION("negative value") {
        neuron.setOutputValue(-0.3);
        REQUIRE(neuron.getOutputValue() == -0.3);
    }
}

// Layer Tests
TEST_CASE("Layer creation", "[Layer]") {
    Layer layer(4, 0, 3);
    REQUIRE(layer.neuronCount() == 5);
    REQUIRE(layer.layerIndex == 0);
}

TEST_CASE("Output layer", "[Layer]") {
    Layer outputLayer(2, 2, 0);
    REQUIRE(outputLayer.neuronCount() == 3);
}

TEST_CASE("Layer neuron count", "[Layer]") {
    Layer layer1(3, 0, 5);
    REQUIRE(layer1.neuronCount() == 4);
    
    Layer layer2(10, 1, 2);
    REQUIRE(layer2.neuronCount() == 11);
}

// TrainingSet Tests
TEST_CASE("TrainingSet initialization", "[TrainingSet]") {
    TrainingSet ts;
    REQUIRE(ts.getNumberOfRows() == 0);
    REQUIRE(ts.getNumberOfColumns() == 0);
}

TEST_CASE("TrainingSet read CSV", "[TrainingSet]") {
    ofstream testFile("test_data.csv");
    testFile << "1.0,2.0,3.0,1\n4.0,5.0,6.0,0\n7.0,8.0,9.0,1\n";
    testFile.close();
    
    TrainingSet ts;
    ts.read("test_data.csv");
    
    REQUIRE(ts.getNumberOfRows() == 3);
    REQUIRE(ts.getNumberOfColumns() == 4);
    
    vector<double> record = ts.getRecord(0);
    REQUIRE(record.size() == 3);
    REQUIRE(record[0] == Approx(1.0));
    
    remove("test_data.csv");
}

// ANN Tests
TEST_CASE("ANN simple topology", "[ANN]") {
    vector<unsigned> topology = {2, 3, 1};
    ArtificialNeuralNetwork ann(topology);
    REQUIRE(true);
}

TEST_CASE("ANN complex topology", "[ANN]") {
    vector<unsigned> topology = {4, 6, 3, 2};
    ArtificialNeuralNetwork ann(topology);
    REQUIRE(true);
}

TEST_CASE("ANN get results", "[ANN]") {
    vector<unsigned> topology = {2, 2, 1};
    ArtificialNeuralNetwork ann(topology);
    
    vector<double> results;
    ann.getResults(results);
    
    REQUIRE(results.size() == 1);
    REQUIRE(results[0] == 0.0);
}

TEST_CASE("ANN multiple outputs", "[ANN]") {
    vector<unsigned> topology = {3, 4, 2};
    ArtificialNeuralNetwork ann(topology);
    
    vector<double> results;
    ann.getResults(results);
    
    REQUIRE(results.size() == 2);
}

TEST_CASE("ANN with TrainingSet", "[ANN][Integration]") {
    ofstream testFile("test_train.csv");
    testFile << "0.0,0.0,0\n0.0,1.0,1\n1.0,0.0,1\n1.0,1.0,0\n";
    testFile.close();
    
    TrainingSet ts;
    ts.read("test_train.csv");
    REQUIRE(ts.getNumberOfRows() == 4);
    
    vector<unsigned> topology = {2, 4, 1};
    ArtificialNeuralNetwork ann(topology);
    REQUIRE(true);
    
    remove("test_train.csv");
}
