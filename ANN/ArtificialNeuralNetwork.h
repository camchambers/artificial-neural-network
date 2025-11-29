#pragma once

#include <vector>
#include "Layer.h"
#include "TrainingSet.h"

class ArtificialNeuralNetwork
{
public:
    /**
     * @brief Construct a new Artificial Neural Network object
     * 
     * @param topology The topology (number of Neurons in each layer) of the neural network
     */
    ArtificialNeuralNetwork(const std::vector<unsigned> &topology);

    /**
     * @brief Back propagate errors allowing the neural network to "learn" 
     * 
     * @param targetValues 
     */
    void backPropagate(const std::vector<double>& targetValues);

    /**
     * @brief Trains an Artificial Neural Network
     * 
     * @param inputVals The input values to the neural network. 
     *  The number of rows in the input value vector must equal
     *  the number of input Neuron in the neural network. 
     */
    void train(TrainingSet &trainingSet);

    /**
     * @brief Feed forward input values through the network for prediction
     * 
     * @param inputValues The input values to feed through the network
     */
    void feedForward(const std::vector<double>& inputValues);

    /**
     * @brief Returns the neural network results
     * 
     * @param resultValues 
     */
    void getResults(std::vector<double>& resultValues) const;

    /**
     * @brief Prints all of the layers of an Artificial Neural Network
     * 
     */
    void print() const;

private:
    std::vector<Layer> layers;
    double error;
};
