#include <iostream>
#include "ArtificialNeuralNetwork.h"

ArtificialNeuralNetwork::ArtificialNeuralNetwork(const vector<unsigned> &topology)
{
    // Print the topology of the Artificial Neural Network
    cout << "Creating a neural network with a ";
    for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
    {
        cout << topology[layerIndex];
        if (layerIndex < (topology.size() - 1))
        {
            cout << ":";
        }
    }
    cout << " toplogy." << endl;

    // Number of connections to the next layer
    unsigned int numberOfOutputs = 0;

    // Create neural network layers
    for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
    {
        unsigned layerSize = topology[layerIndex];

        cout << endl
             << "Adding a " << layerSize << " neuron layer to the neural network." << endl;

        // Pass in the number of connections for all Neurons in the layer to be constructed
        // The last layer will not contain any connections, since it is an output layer
        numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;

        layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
    }
};

void ArtificialNeuralNetwork::print()
{
    cout << endl
         << "Printing neural network:" << endl
         << endl;

    for (unsigned layerIndex = 0; layerIndex < layers.size(); ++layerIndex)
    {
        cout << "Layer " << (layerIndex + 1) << endl;
        layers[layerIndex].print();
        cout << endl;
    }
    cout << endl;
};

void ArtificialNeuralNetwork::train(const vector<double> inputVals)
{
    cout << "Training Neural Network" << endl;

    unsigned inputLayerSize = layers[0].neuronCount();

    // Validate that the rows of the input vector to the Neural Network matches
    // the number of Neurons in the first layer (input Neurons) of the Neural Network
    if (inputVals.size() != inputLayerSize)
    {
        cout << endl
             << "Error: The number of input values does not match the number of input neurons in the Neural Network." << endl
             << endl;
        exit(1);
    }

    // Assign (latch) input values to the Neurons of the input Layer
    for (unsigned i = 0; i < inputLayerSize; i++)
    {
        layers[0].neurons[i].setOutputValue(inputVals[i]);
    }

    // Forward propogate input values
    // Skip the input layer because the output values for the input layer
    // have already been set
    for (unsigned layerIndex = 1; layerIndex < layers.size(); ++layerIndex)
    {
        Layer &previousLayer = layers[layerIndex - 1];
        for (unsigned neuronIndex = 0; neuronIndex < layers[layerIndex].neuronCount(); ++neuronIndex)
        {
            layers[layerIndex].neurons[neuronIndex].feedForward(previousLayer);
        }
    }
};
