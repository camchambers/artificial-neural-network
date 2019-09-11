/**
 * Artificial Neural Network 
 * 
 * An object-oriented implementation of an artificial neural network
 */

#include <iostream>
#include <iomanip>
#include "TrainingSet.h"
#include "ArtificialNeuralNetwork.h"

using namespace std;

int main(int argc, char *argv[])
{

    // Validate that a training set csv was passed in as an argument
    if (argc != 2)
    {
        cout << "Error: please specify a CSV training set filename." << endl
             << endl;
        exit(1);
    }

    // TODO validate file exists

    // TODO validate file is of type CSV

    // Set the filename based on the argument passed in
    string fileName = argv[1];

    cout << endl
         << "ARTIFICIAL NERAL NETWORK" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(2);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Instantiate a new training set
    TrainingSet trainingSet;

    // Read training set from a file
    cout << "Reading training set." << endl
         << endl;
    trainingSet.read(fileName);
    cout << "Done." << endl
         << endl;

    // Print training set
    cout << "Printing training set." << endl
         << endl;
    trainingSet.print();

    // Create a vector to store a topology
    vector<unsigned> topology = {4, 6, 3, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Print the contents of the neural network
    ann.print();

    // Train the neural network
    ann.train(trainingSet);

    // Wait for user input before terminating
    cout << "Press any key to continue...";
    cin.get();

    return 0;
}