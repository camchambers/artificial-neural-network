#include <iostream>
#include "Neuron.h"
#include "Layer.h"

using namespace std;

Layer::Layer(unsigned numberOfNeurons, unsigned index, unsigned numberOfOutputs)
{
    // Assign layer index
    layerIndex = index;

    // Populate the Layer with Neurons based on the numberOfNeurons parameter
    for (unsigned neuronIndex = 0; neuronIndex < numberOfNeurons; ++neuronIndex)
    {
        cout << "\tAdding neuron " << (neuronIndex + 1) << " to layer " << layerIndex + 1 << "." << endl;
        neurons.push_back(Neuron(neuronIndex, numberOfOutputs));
    }
}

unsigned Layer::neuronCount()
{
    return neurons.size();
}

void Layer::print()
{
    for (unsigned neuronIndex = 0; neuronIndex < neurons.size(); ++neuronIndex)
    {
        neurons[neuronIndex].print();
    }
}

// Forward definition for Neuron feed forward
void Neuron::feedForward(Layer &previousLayer)
{

    // Display which neuron in which layer is feeding forward
    cout << "\tLayer " << previousLayer.layerIndex + 2 << ", Neuron " << this->neuronIndex + 1 << " is feeding forward." << endl;

    // The sum of the inputs
    double sum = 0.0;

    // Loop through all of the neurons in the previous layer
    for (unsigned neuronIndex = 0; neuronIndex < previousLayer.neuronCount(); ++neuronIndex)
    {
        sum = sum + previousLayer.neurons[neuronIndex].getOutputValue() * previousLayer.neurons[neuronIndex].connections[this->neuronIndex].weight;
    }


}