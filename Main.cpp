#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// TODO Separate classes into individual files

class Connection
{

public:
    Connection()
    {
        weight = (double)rand() / RAND_MAX * 2.0 - 1.0;
    }
    double weight;
    double deltaWeight;

    void print(unsigned connectionIndex)
    {
        cout << "(" << (weight < 0 ? " " : "") << weight << ")";
    }
};

class Neuron
{

public:
    Neuron(unsigned numberOfOutputConnections)
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

    void print(unsigned neuronIndex)
    {
        // Create layer nodes based on the number of neurons specified
        cout << "\tNeuron " << neuronIndex + 1 << " ";
        for (unsigned connectionIndex = 0; connectionIndex < connections.size(); ++connectionIndex)
        {

            connections[connectionIndex].print(connectionIndex);
        }
        cout << endl;
    }

private:
    vector<Connection> connections;
};

class Layer
{
public:
    unsigned layerIndex;
    vector<Neuron> neurons;

    Layer(unsigned numberOfNeurons, unsigned index, unsigned numberOfOutputs)
    {
        // Assign layer index
        layerIndex = index;

        // Create layer nodes based on the number of neurons specified
        for (unsigned neuronIndex = 0; neuronIndex < numberOfNeurons; ++neuronIndex)
        {
            cout << "Adding node " << (neuronIndex + 1) << " to layer " << layerIndex + 1 << "." << endl;
            neurons.push_back(Neuron(numberOfOutputs));
        }
    }

    void print()
    {
        for (unsigned neuronIndex = 0; neuronIndex < neurons.size(); ++neuronIndex)
        {
            neurons[neuronIndex].print(neuronIndex);
        }
    }
};

class ArtificialNeuralNetwork
{
public:
    ArtificialNeuralNetwork(const vector<unsigned> &topology)
    {

        // Print network topology
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
                 << "Adding a " << layerSize << " node layer to the neural network."
                 << endl;

            // Need to pass in  the number of connections in the net layer
            numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;

            layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
        }
    };

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

    void train(vector<double> &inputVals)
    {
        cout << "Training Neural Network" << endl;
    };

private:
    vector<Layer> layers;
};

int main()
{
    cout << "ARTIFICIAL NERAL NETWORK" << endl
         << endl;

    // Define number of decimal places for printing output
    cout << fixed << setprecision(4);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Create a vector to store a topology
    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(4);
    topology.push_back(2);

    // Instantiate a new neural network
    ArtificialNeuralNetwork ann(topology);

    // Print neural network contents
    ann.print();

    // Train neural network
    vector<double> inputVals;
    ann.train(inputVals);

    return 0;
}