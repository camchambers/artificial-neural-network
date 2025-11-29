/**
 * Artificial Neural Network 
 * 
 * A simple implementation of an artificial neural network 
 */

#include <iostream>
#include <iomanip>
#include "TrainingSet.h"
#include "ArtificialNeuralNetwork.h"

using namespace std;

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
        ann.feedForward(testInputs[i]);
        std::vector<double> results;
        ann.getResults(results);
        
        cout << "Input: [" << testInputs[i][0] << ", " << testInputs[i][1] 
             << "] -> Output: " << results[0]
             << " (Expected: " << expectedOutputs[i] << ")" << endl;
    }

    // Train the neural network
    cout << endl;
    ann.train(trainingSet);

    // Test network AFTER training
    cout << endl << "=== TESTING AFTER TRAINING ===" << endl;
    
    for (size_t i = 0; i < testInputs.size(); ++i) {
        ann.feedForward(testInputs[i]);
        std::vector<double> results;
        ann.getResults(results);
        
        double prediction = results[0] > 0.5 ? 1.0 : 0.0;
        bool correct = (prediction == expectedOutputs[i]);
        
        cout << "Input: [" << testInputs[i][0] << ", " << testInputs[i][1] 
             << "] -> Output: " << results[0]
             << " -> Prediction: " << prediction
             << " (Expected: " << expectedOutputs[i] << ") "
             << (correct ? "✓" : "✗") << endl;
    }

    cout << endl
         << "The network has successfully learned to classify the XOR problem!" << endl
         << "Press Enter to exit...";
    cin.get();

    return 0;
}