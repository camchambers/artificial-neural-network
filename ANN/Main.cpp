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
         << "ARTIFICIAL NERAL NETWORK" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(2);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));
 
    // Create a vector to store a topology
    vector<unsigned> topology = {4, 6, 3, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Print the contents of the neural network
    ann.print();
  
    // Wait for user input before terminating
    cout << "Press any key to continue...";
    cin.get();

    return 0;
}