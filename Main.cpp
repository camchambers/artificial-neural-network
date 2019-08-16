#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// TODO Separate classes into individual files

/**
 * @brief Connections link neurons and define how strongly linked neurons 
 * are according to a weight value
 * 
 */
class Connection
{
public:
    /**
     * @brief Construct a new Connection object
     * 
     */
    Connection()
    {
        weight = (double)rand() / RAND_MAX * 2.0 - 1.0;
    }

    // The weight of a connection between neurons
    double weight;

    // The change in the weight between epochs
    double deltaWeight;

    /**
     * @brief Prints the weight of a Connection
     * 
     * @param connectionIndex 
     */
    void print()
    {
        cout << "(" << (weight < 0 ? " " : "") << weight << ")";
    }
};

/**
 * @brief Neurons are the building blocks of an Artificial Neural Network and 
 * drive the input to specific output nodes according to the values of connection
 * weights between neurons
 * 
 */
class Neuron
{
public:
    /**
     * @brief Construct a new Neuron object
     * 
     * @param numberOfOutputConnections The number of the connections in the 
     * following layer. Since the final layer contains the output nodes to the 
     * Artificial Neural Network, they will not contain output connections
     */
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

    /**
     * @brief Prints all of the Connections of a Neuron
     * 
     * @param neuronIndex 
     */
    void print(unsigned neuronIndex)
    {
        cout << "\tNeuron " << neuronIndex + 1 << " ";
        for (auto connection : connections)
        {
            connection.print();
        }
        cout << endl;
    }

private:
    vector<Connection> connections;
    double outputValue = 0;
};

/**
 * @brief Layers contains rows of neurons. The first layer (the input layer) 
 * serves as input to the Artificial Neural Network. Internal layers (hidden
 * layers) form linkages between nodes. The last layer (output layer) contains
 * output to the Neural Network. Commonly, the number of output nodes 
 * corresponds to the number of class labels in the classification problem.
 * 
 */
class Layer
{
public:
    unsigned layerIndex;
    vector<Neuron> neurons;

    /**
     * @brief Construct a new Layer object
     * 
     * @param numberOfNeurons The number of Neurons the layer will contain
     * @param index The index of the layer being created
     * @param numberOfOutputs The number of output Connections that the Neurons
     * in the Layer will contain
     */
    Layer(unsigned numberOfNeurons, unsigned index, unsigned numberOfOutputs)
    {
        // Assign layer index
        layerIndex = index;

        // Populate the Layer with Neurons based on the numberOfNeurons parameter
        for (unsigned neuronIndex = 0; neuronIndex < numberOfNeurons; ++neuronIndex)
        {
            cout << "Adding node " << (neuronIndex + 1) << " to layer " << layerIndex + 1 << "." << endl;
            neurons.push_back(Neuron(numberOfOutputs));
        }
    }

    /**
     * @brief Prints the number of neurons in the layer
     * 
     */
    unsigned neuronCount(){
        return neurons.size();
    }

    /**
     * @brief Prints all of the Neurons of a Layer
     * 
     */
    void print()
    {
        unsigned neuronIndex = 0;
        for (auto neuron : neurons)
        {
            neuron.print(neuronIndex++);
        }
    }
};

class ArtificialNeuralNetwork
{
public:
    /**
     * @brief Construct a new Artificial Neural Network object
     * 
     * @param topology The topology (number of nodes in each layer) of the neural network
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
                 << "Adding a " << layerSize << " node layer to the neural network."
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
     *  the number of input nodes in the neural network. 
     */
    void train(const vector<double> inputVals)
    {
        cout << "Training Neural Network" << endl;

        unsigned inputLayerSize = layers[0].neuronCount();

        // Validate that the rows of the input vector to the Neural Network matches
        // the number of Neurons in the first layer (input Neurons) of the Neural Network
        if (inputVals.size() != inputLayerSize)
        {
            cout << endl << "Error: The number of input values does not match the number of input nodes in the Neural Network." << endl << endl;
            exit(1);
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
    cout << fixed << setprecision(4);

    // Provide a seed for random number generation
    srand(static_cast<unsigned int>(clock()));

    // Create a vector to store a topology
    vector<unsigned> topology = {8, 6, 4, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Print neural network contents
    ann.print();

    // Define input to the artificial neural network
    vector<double> inputVals = {2.24, 6, 41, 7.48};

    // Train the neural network
    ann.train(inputVals);

    // Wait for user input before terminating
    cout << "Press any key to continue...";
    cin.get();

    return 0;
}