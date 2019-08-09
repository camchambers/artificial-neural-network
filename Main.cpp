#include <iostream>
#include <vector>

using namespace std;

// TODO Separate classes into individual files

class Connection
{
public:
    Connection()
    {
        weight = 0;
    }
    double weight;
    double deltaWeight;
    void print()
    {
        cout << " (" << weight << ") ";
    }
};

class Neuron
{
public:
    Neuron()
    {
        connections.push_back(Connection());
    }
    void print()
    {
        // Create layer nodes based on the number of neurons specified
        for (unsigned connectionIndex = 0; connectionIndex < connections.size(); ++connectionIndex)
        {
            connections[connectionIndex].print();
        }
    }

private:
    vector<Connection> connections;
};

class Layer
{
public:
    unsigned layerIndex;
    vector<Neuron> neurons;

    Layer(unsigned numberOfNeurons, unsigned index)
    {
        // Assign layer index
        layerIndex = index;

        // Create layer nodes based on the number of neurons specified
        for (unsigned neuronIndex = 0; neuronIndex < numberOfNeurons; ++neuronIndex)
        {
            cout << "Adding node " << (neuronIndex + 1) << " to layer " << layerIndex + 1 << "." << endl;
            neurons.push_back(Neuron());
        }
    }

    void print()
    {
        for (unsigned neuronIndex = 0; neuronIndex < neurons.size(); ++neuronIndex)
        {
            neurons[neuronIndex].print();
        }
    }
};

class ArtificialNeuralNetwork
{

public:
    ArtificialNeuralNetwork(const vector<unsigned> &topology)
    {

        // Print network topology
        cout << "Generating a neural network with a ";
        for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
        {
            cout << topology[layerIndex];
            if (layerIndex < (topology.size() -1)){
                cout << ":";
            }
        }
        cout << " toplogy." << endl;

        // Create neural network layers
        for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
        {
            unsigned layerSize = topology[layerIndex];
            cout << endl
                 << "Adding a " << layerSize << " node layer to the neural network." << endl;
            layers.push_back(Layer(layerSize, layerIndex));
        }
    }

    // Prints values of each node for neural network
    void print()
    {
        cout << endl
             << "Printing neural network:" << endl;
        for (unsigned layerIndex = 0; layerIndex < layers.size(); ++layerIndex)
        {
            cout << "Layer " << (layerIndex + 1) << ": ";
            layers[layerIndex].print();
            cout << endl;
        }
        cout << endl;
    }

private:
    vector<Layer> layers;
};

int main()
{

    cout << "ARTIFICIAL NERAL NETWORK" << endl << endl;

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Create a vector to store a topology
    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(5);
    topology.push_back(2);

    // Instantiate a new neural network
    ArtificialNeuralNetwork ann(topology);
    ann.print();

    return 0;
}