#include <iostream>
#include <vector>

using namespace std;

// TODO Separate classes into individual files

class Connection
{
    double weight;
};

class Neuron
{
public:
    Neuron();

private:
    vector<Connection> connections;
};

class Layer
{
public:
    vector<Neuron> neurons;

    Layer(unsigned numberOfNeurons)
    {
        for (unsigned nodeIndex = 0; nodeIndex < numberOfNeurons; ++nodeIndex)
        {
            cout << "Adding node " << (nodeIndex + 1) << " to layer." << endl;
    
        }
    }
};

class ArtificialNeuralNetwork
{

public:
    ArtificialNeuralNetwork(const vector<unsigned> &topology)
    {

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