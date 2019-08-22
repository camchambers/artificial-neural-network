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
        cout << "Adding neuron " << (neuronIndex + 1) << " to layer " << layerIndex + 1 << "." << endl;
        neurons.push_back(Neuron(numberOfOutputs));
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
        neurons[neuronIndex].print(neuronIndex);
    }
}

// Forward definition for Neuron feed forward
void Neuron::feedForward(Layer &previousLayer)
{
    // testing
    cout << endl << "Feeding forward neuron in layer " << previousLayer.layerIndex << endl;
}
