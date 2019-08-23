#pragma once
#include <vector>
#include "Connection.h"

using namespace std;

class Layer;

/**
 * @brief Neurons are the building blocks of an Artificial Neural Network and 
 * drive the input to specific output Neurons according to the values of connection
 * weights between neurons
 * 
 */
class Neuron
{
public:
    /**
     * @brief Construct a new Neuron object
     * 
     * @param numberOfOutputConnections The number of the connections in the 
     * following layer. Since the final layer contains the output Neurons to the 
     * Artificial Neural Network, they will not contain output connections
     */
    Neuron(unsigned neuronIndex, unsigned numberOfOutputConnections);

    /**
     * @brief Sets the output value of the current Neuron
     * 
     * @param value The output value to set for the current neuron
     */
    void setOutputValue(double value);

    /**
     * @brief Gets the output value of the current Neuron
     * 
     */
    double getOutputValue();

    /**
     * @brief Feeds forward outputs from the previous layer into the current neuron
     * 
     * @param previousLayer 
     */
    void feedForward(Layer &previousLayer);

    /**
     * @brief Calculates the gradients of hidden layer neurons during back propagation
     * 
     * @param nextLayer 
     * @return double 
     */
    void calculateHiddenGradients(Layer &nextLayer);

    /**
     * @brief Calculates the gradients of output layer neurons during back propagation
     * 
     * @param targetValues 
     * @return double 
     */
    double calculateOutputGradients(double targetValue);

    /**
     * @brief Updates the input weights for the current neuron during backpropagation
     * 
     * @return double 
     */
    double updateInputWeights(Layer &layer);

    /**
     * @brief Prints all of the Connections of a Neuron
     * 
     * @param neuronIndex 
     */
    void print();

private:
    vector<Connection> connections;
    unsigned neuronIndex = 0;
    double outputValue = 0.0;
    double gradient = 0.0;

    /**
     * @brief Shapes the output of a Neuron by applying a mathematical formula
     * 
     * @param input The input to the activation function
     * @return double 
     */
    double activationFunction(double input);

    /**
     * @brief Retruns an approximation of the derivative of the input
     * 
     */
    double activationFunctionDerivative(double input);

    /**
     * @brief Determines the sum of the derivatives of the weights of a layer
     * 
     * @param nextLayer 
     * @return double 
     */
    double sumDerivativeOfWeights(Layer &nextLayer);
};