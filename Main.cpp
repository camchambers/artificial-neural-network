/**
 * Artificial Neural Network 
 * 
 * An object-oriented implementation of an artificial neural network
 */

#include <iostream>
#include <iomanip>
#include "ArtificialNeuralNetwork.h"

using namespace std;

int main()
{
    cout << "ARTIFICIAL NERAL NETWORK" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(2);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Create a vector to store a topology
    vector<unsigned> topology = {4, 6, 3, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Print neural network contents
    ann.print();

    // Define input to the artificial neural network
    vector<double> inputVals = {2.24, 6, 41, 7.48};

    // Train the neural network
    ann.train(inputVals);

    // Re-print the neural network after input values have been updated
    ann.print();

    // Define a results vector
    vector<double> resultValues;

    // Get results
    ann.getResults(resultValues);

    // Wait for user input before terminating
    cout << "Press any key to continue...";
    cin.get();

    return 0;
}