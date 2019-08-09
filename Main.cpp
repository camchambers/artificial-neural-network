#include <iostream>
#include <vector>

using namespace std;

// TODO Separate classes into individual files

class Node
{
};

class Layer
{
public:
    vector<Node> nodes;
    Layer(int numberOfNodes)
    {
        for (unsigned nodeIndex = 0; nodeIndex < numberOfNodes; ++nodeIndex)
        {
            cout << "Adding node " << nodeIndex << " to layer." << endl;
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
            cout << "Adding a " << topology[layerIndex] << " node layer to the neural network." << endl;
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