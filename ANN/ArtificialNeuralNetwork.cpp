#include <iostream>
#include <cmath>
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
    cout << " toplogy.";

    // Number of connections to the next layer
    unsigned int numberOfOutputs = 0;

    // Create neural network layers
    for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
    {
        unsigned layerSize = topology[layerIndex];

        // The number of connections for all Neurons in the layer to be constructed
        // The last layer will not contain any connections, since it is an output layer
        numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;

        cout << endl
             << endl
             << "Adding a " << layerSize << " neuron layer to the neural network";

        layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
    }
};

void ArtificialNeuralNetwork::backPropagate(const vector<double> targetValues)
{
    // A convienance pointer to last layer in the neural network
    Layer &outputLayer = layers.back();

    // Reset the error of the neural network
    this->error = 0.0;

    for (unsigned neuronIndex = 0; neuronIndex < outputLayer.neuronCount() - 1; ++neuronIndex)
    {
        // Determine the error for the current output node by taking the delta
        // (difference) between the output value and expected value
        double delta = targetValues[neuronIndex] - outputLayer.neurons[neuronIndex].getOutputValue();

        // Accumulate the squared error for each of the output neurons
        this->error = this->error + delta * delta;
    }

    // Get the average of the squared error
    this->error = this->error / outputLayer.neuronCount();

    // Take the square root of the average squared error to get the RMS (the
    // back propagation function aims to minimize the RMS of the output Neurons)
    this->error = sqrt(this->error);

    // Calculate the output layer gradients
    for (unsigned neuronIndex = 0; neuronIndex < outputLayer.neuronCount() - 1; ++neuronIndex)
    {
        outputLayer.neurons[neuronIndex].calculateOutputGradients(targetValues[neuronIndex]);
    }

    // Calculate the gradients of the hidden layers
    for (unsigned layerIndex = layers.size() - 2; layerIndex > 0; --layerIndex)
    {
        // A convienance variable for the current hidden layer
        Layer &hiddenLayer = layers[layerIndex];

        // A convienance variable for the next layer relative to the current one
        Layer &nextLayer = layers[layerIndex + 1];

        // Iterate through all of the neurons in the current hidden layer and
        // tell each neuron to calculate their gradients
        for (unsigned neuronIndex = 0; neuronIndex < hiddenLayer.neuronCount(); ++neuronIndex)
        {
            hiddenLayer.neurons[neuronIndex].calculateHiddenGradients(nextLayer);
        }
    }

    // Update connection weights for all layers, except for
    // the input layer
    for (unsigned layerIndex = layers.size() - 1; layerIndex > 0; --layerIndex)
    {
        // A convienance variable for the current hidden layer
        Layer &layer = layers[layerIndex];

        // A convienance variable for the next layer relative to the current one
        Layer &previousLayer = layers[layerIndex - 1];

        // Iterate over each neuron in the current later and tell the neuron to
        // update its input weights
        for (unsigned neuronIndex = 0; neuronIndex < layer.neuronCount() - 1; ++neuronIndex)
        {
            layer.neurons[neuronIndex].updateInputWeights(previousLayer);
        }
    }
}

void ArtificialNeuralNetwork::print()
{
    cout << endl
         << endl
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

void ArtificialNeuralNetwork::train(TrainingSet &trainingSet)
{
    cout << endl
         << "Training Neural Network" << endl;

    unsigned inputLayerSize = layers[0].neuronCount();

    // Iterate over training set
    for (int recordIndex = 0; recordIndex < trainingSet.getNumberOfRows() - 1; recordIndex++)
    {
        cout << endl
             << "Training neural network with record " << recordIndex + 1 << "." << endl
             << endl;

        vector<double> inputValues = trainingSet.getRecord(recordIndex);

        // Validate that the rows of the input vector to the Neural Network matches
        // the number of Neurons in the first layer (input Neurons) of the Neural Network
        if (inputValues.size() != inputLayerSize - 1)
        {
            cout << endl
                 << "Error: The number of input values (" << inputValues.size()
                 << ") does not match the number of input neurons ("
                 << inputLayerSize - 1 << ") in the Neural Network."
                 << endl
                 << endl;
            exit(1);
        }

        // Assign (latch) input values to the Neurons of the input Layer
        for (unsigned i = 0; i < inputLayerSize; i++)
        {
            layers[0].neurons[i].setOutputValue(inputValues[i]);
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

        this->print();
    }

    cout << endl
         << "Training complete" << endl
         << endl;
};

void ArtificialNeuralNetwork::getResults(vector<double> resultValues)
{
    resultValues.clear();

    // Loops through all of the layers in the output layers
    for (unsigned neuronIndex = 0; neuronIndex < layers.back().neuronCount() - 1; ++neuronIndex)
    {
        resultValues.push_back(layers.back().neurons[neuronIndex].getOutputValue());
    }
}