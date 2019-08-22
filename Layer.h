#pragma once
#include "Neuron.h"

using namespace std;

class Layer
{
public:
    unsigned layerIndex;
    vector<Neuron> neurons;

    /**
     * @brief Construct a new Layer object
     * 
     * @param numberOfNeurons The number of Neurons the layer will contain
     * @param index The index of the layer being created
     * @param numberOfOutputs The number of output Connections that the Neurons
     * in the Layer will contain
     */
    Layer(unsigned numberOfNeurons, unsigned index, unsigned numberOfOutputs);
    
    /**
     * @brief Prints the number of neurons in the layer
     * 
     */
    unsigned neuronCount();

    /**
     * @brief Prints all of the Neurons of a Layer
     * 
     */
    void print();
};