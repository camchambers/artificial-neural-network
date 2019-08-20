#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#include "Connection.h"
#include "Neuron.h"
#include "Layer.h"

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
    unsigned neuronIndex = 0;
    for (neuronIndex = 0; neuronIndex < neurons.size(); ++neuronIndex)
    {
        neurons[neuronIndex].print(neuronIndex++);
    }
}
}
;

class ArtificialNeuralNetwork
{
public:
    /**
     * @brief Construct a new Artificial Neural Network object
     * 
     * @param topology The topology (number of Neurons in each layer) of the neural network
     */
    ArtificialNeuralNetwork(const vector<unsigned> &topology)
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
                 << "Adding a " << layerSize << " neuron layer to the neural network."
                 << endl;

            // Pass in the number of connections for all Neurons in the layer to be constructed
            // The last layer will not contain any connections, since it is an output layer
            numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;

            layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
        }
    };

    /**
     * @brief Prints all of the layers of an Artificial Neural Network
     * 
     */
    void print()
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

    /**
     * @brief Trains an Artificial Neural Network
     * 
     * @param inputVals The input values to the neural network. 
     *  The number of rows in the input value vector must equal
     *  the number of input Neuron in the neural network. 
     */
    void train(const vector<double> inputVals)
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
            cout << endl
                 << "Layer " << layerIndex << endl;
            for (unsigned neuronIndex = 0; neuronIndex < layers[layerIndex].neuronCount(); ++neuronIndex)
            {
                cout << endl
                     << "\tNeuron " << neuronIndex << endl;
            }
        }
    };

private:
    vector<Layer> layers;
};

int main()
{
    cout << "ARTIFICIAL NERAL NETWORK" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(2);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Create a vector to store a topology
    vector<unsigned> topology = {4, 6, 3, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Print neural network contents
    ann.print();

    // Define input to the artificial neural network
    vector<double> inputVals = {2.24, 6, 41, 7.48};

    // Train the neural network
    ann.train(inputVals);

    // Re-print the neural network after input values have been updated
    ann.print();

    // Wait for user input before terminating
    cout << "Press any key to continue...";
    cin.get();

    return 0;
}