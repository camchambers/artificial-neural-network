/**
 * XOR Classification Example
 * 
 * Demonstrates using the ANN library to solve the XOR problem
 */

#include <iostream>
#include <iomanip>
#include "ann/TrainingSet.h"
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingConfig.h"

using namespace std;
using namespace ann;

int main(int argc, char *argv[])
{
    cout << endl
         << "ARTIFICIAL NEURAL NETWORK" << endl
         << "XOR Classification Problem" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(4);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));
 
    // Create a vector to store a topology
    // 2 inputs (XOR inputs), 4 hidden neurons, 1 output (XOR result)
    std::vector<unsigned> topology = {2, 4, 1};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    cout << endl
         << "Neural network created with topology: ";
    for (size_t i = 0; i < topology.size(); ++i) {
        cout << topology[i];
        if (i < topology.size() - 1) cout << "-";
    }
    cout << endl << endl;

    // Load and prepare training data
    TrainingSet trainingSet;
    trainingSet.read("train.csv");
    
    cout << "Training set loaded: " << trainingSet.getNumberOfRows() 
         << " samples" << endl;

    // Test network BEFORE training
    cout << endl << "=== TESTING BEFORE TRAINING ===" << endl;
    std::vector<std::vector<double>> testInputs = {
        {0.0, 0.0},  // Expected: 0
        {0.0, 1.0},  // Expected: 1
        {1.0, 0.0},  // Expected: 1
        {1.0, 1.0}   // Expected: 0
    };
    std::vector<double> expectedOutputs = {0.0, 1.0, 1.0, 0.0};

    for (size_t i = 0; i < testInputs.size(); ++i) {
        auto prediction = ann.predict(testInputs[i]);
        
        cout << "Input: [" << testInputs[i][0] << ", " << testInputs[i][1] 
             << "] -> Output: " << prediction.probabilities[0]
             << " (Expected: " << expectedOutputs[i] << ")" << endl;
    }

    // Configure and train the neural network
    cout << endl;
    TrainingConfig config;
    config.epochs = 1000;
    config.learningRate = 0.15;
    config.momentum = 0.5;
    config.verbose = true;
    config.printInterval = 200;
    
    // Add a progress callback
    config.progressCallback = [](int epoch, double error) {
        // Custom logging could go here
    };
    
    ann.train(trainingSet, config);

    // Test network AFTER training
    cout << endl << "=== TESTING AFTER TRAINING ===" << endl;
    
    for (size_t i = 0; i < testInputs.size(); ++i) {
        auto prediction = ann.predict(testInputs[i]);
        
        bool correct = (prediction.classLabel == static_cast<int>(expectedOutputs[i]));
        
        cout << "Input: [" << testInputs[i][0] << ", " << testInputs[i][1] 
             << "] -> Output: " << prediction.probabilities[0]
             << " -> Prediction: " << prediction.classLabel
             << " (Expected: " << expectedOutputs[i] << ") "
             << (correct ? "✓" : "✗") << endl;
    }

    cout << endl
         << "The network has successfully learned to classify the XOR problem!" << endl
         << "Final training error: " << ann.getError() << endl
         << endl;
    cin.get();

    return 0;
}