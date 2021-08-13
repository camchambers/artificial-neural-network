#pragma once

#include <vector>
#include "Layer.h"
#include "TrainingSet.h"

using namespace std;

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
     * @brief Back propagate errors allowing the neural network to "learn" 
     * 
     * @param targetValues 
     */
    void backPropagate(const vector<double> targetValues);

    /**
     * @brief Trains an Artificial Neural Network
     * 
     * @param inputVals The input values to the neural network. 
     *  The number of rows in the input value vector must equal
     *  the number of input Neuron in the neural network. 
     */
    void train(TrainingSet &trainingSet);

    /**
     * @brief Returns the neural network results
     * 
     * @param inputVals 
     */
    void getResults(vector<double> resultValues);

    /**
     * @brief Prints all of the layers of an Artificial Neural Network
     * 
     */
    void print();

private:
    vector<Layer> layers;
    double error;
};
