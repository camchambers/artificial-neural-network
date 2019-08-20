using namespace std;

#include <vector>
#include "Connection.h"
#include "Neuron.h"
#include "Layer.h"

#pragma once

class ArtificialNeuralNetwork
{
public:
    /**
     * @brief Construct a new Artificial Neural Network object
     * 
     * @param topology The topology (number of Neurons in each layer) of the neural network
     */
    ArtificialNeuralNetwork(const vector<unsigned> &topology);

    /**
     * @brief Prints all of the layers of an Artificial Neural Network
     * 
     */
    void print();

    /**
     * @brief Trains an Artificial Neural Network
     * 
     * @param inputVals The input values to the neural network. 
     *  The number of rows in the input value vector must equal
     *  the number of input Neuron in the neural network. 
     */
    void train(const vector<double> inputVals);

private:
    vector<Layer> layers;
};
