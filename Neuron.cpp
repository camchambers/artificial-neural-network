#include <iostream>
#include <cmath>
#include "Neuron.h"

Neuron::Neuron(unsigned neuronIndex, unsigned numberOfOutputConnections)
{
    // Set the index of the current neuron
    this->neuronIndex = neuronIndex;

    // Create connections for each neuron
    if (numberOfOutputConnections > 0)
    {
        for (unsigned connectionIndex = 0; connectionIndex < numberOfOutputConnections; ++connectionIndex)
        {
            cout << "\t\tAdding connection " << (connectionIndex + 1) << " with " << numberOfOutputConnections << " outputs" << endl;
            connections.push_back(Connection());
        }
    }
}

double Neuron::getOutputValue()
{
    return outputValue;
}

void Neuron::setOutputValue(double value)
{
    outputValue = value;
}

double Neuron::activationFunction(double input)
{
    return tanh(input);
}

double Neuron::activationFunctionDerivative(double input)
{
    return 1.0 - input * input;
}

double Neuron::calculateHiddenGradients(Layer &nextLayer)
{
    return 0.0;
}

void Neuron::print()
{
    cout << "\tNeuron " << neuronIndex + 1 << " ";
    for (auto connection : connections)
    {
        cout << "(" << outputValue << ",";
        connection.print();
        cout << ")";
    }
    cout << endl;
}