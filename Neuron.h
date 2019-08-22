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

    void feedForward(Layer &previousLayer);

    /**
     * @brief Prints all of the Connections of a Neuron
     * 
     * @param neuronIndex 
     */
    void print();

private:
    vector<Connection> connections;
    unsigned neuronIndex = 0;
    double outputValue = 0;
};