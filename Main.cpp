#include <iostream>
#include <vector>

using namespace std;

// TODO Separate classes into individual files

class Connection
{
public:
    double weight;
};

class Neuron
{

private:
    vector<Connection> connections;
};

class Layer
{
public:
    vector<Neuron> neurons;

    Layer(unsigned numberOfNeurons)
    {
        // Create layer nodes based on the number of neurons specified
        for (unsigned nodeIndex = 0; nodeIndex < numberOfNeurons; ++nodeIndex)
        {
            cout << "Adding node " << (nodeIndex + 1) << " to layer." << endl;
            neurons.push_back(Neuron());
        }
    }
};

class ArtificialNeuralNetwork
{

public:
    ArtificialNeuralNetwork(const vector<unsigned> &topology)
    {

        // Create neural network layers
        for (unsigned layerIndex = 0; layerIndex < topology.size(); ++layerIndex)
        {
            unsigned layerSize = topology[layerIndex];
            cout << "Adding a " << layerSize << " node layer to the neural network." << endl;
            layers.push_back(Layer(layerSize));
        }
    }

private:
    vector<Layer> layers;
};

int main()
{
    cout << "ARTIFICIAL NERAL NETWORK" << endl;

    // Create a vector to store a topology
    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(5);
    topology.push_back(2);

    // Instantiate a new neural network
    ArtificialNeuralNetwork ann(topology);

    return 0;
}