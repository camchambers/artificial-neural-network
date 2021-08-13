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
            cout << endl
                 << "\t\tAdding connection " << (connectionIndex + 1) << " with " << numberOfOutputConnections << " outputs";
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

void Neuron::calculateHiddenGradients(Layer &nextLayer)
{
    // The error difference in this case is calculated by taking the sum of the
    // derivatives of the weights of the next layer because we don't have a
    // target value that we can compare with
    // The equivalent of the error delta is the sum of the derivatives of the next layer
    double sumDerivativeOfWeights = 0.0;
}

void Neuron::calculateOutputGradients(double targetValue)
{
    // Compare the output value the neuron to the target value that it's supposed to have
    double delta = targetValue - this->outputValue;

    // Multiply the delta by the derivative of the neuron's output value
    // causing the output of the neural network to reduce its overall error
    this->gradient = Neuron::activationFunctionDerivative(outputValue);
}

double Neuron::learningRate = 0.15;

double Neuron::momentumValue = 0.5;

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