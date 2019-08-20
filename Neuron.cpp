using namespace std;
#include <iostream>
#include "Neuron.h"

Neuron::Neuron(unsigned numberOfOutputConnections)
{
    // Create connections for each neuron
    if (numberOfOutputConnections > 0)
    {
        for (unsigned connectionIndex = 0; connectionIndex < numberOfOutputConnections; ++connectionIndex)
        {
            cout << "Adding connection " << (connectionIndex + 1) << " with " << numberOfOutputConnections << " outputs" << endl;
            connections.push_back(Connection());
        }
    }
}

void Neuron::setOutputValue(double value)
{
    outputValue = value;
}

void Neuron::print(unsigned neuronIndex)
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