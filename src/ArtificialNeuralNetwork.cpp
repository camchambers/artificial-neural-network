#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingSet.h"
#include "Layer.h"

using namespace std;

namespace ann {

ArtificialNeuralNetwork::ArtificialNeuralNetwork(const std::vector<unsigned> &topology)
{
    // Number of connections to the next layer
    unsigned int numberOfOutputs = 0;

    // Create neural network layers
    for (auto layerIndex = 0u; layerIndex < topology.size(); ++layerIndex)
    {
        auto layerSize = topology[layerIndex];

        // The number of connections for all Neurons in the layer to be constructed
        // The last layer will not contain any connections, since it is an output layer
        numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;

        layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
    }
}

ArtificialNeuralNetwork::~ArtificialNeuralNetwork()
{
    // Default destructor
}

void ArtificialNeuralNetwork::backPropagate(const std::vector<double>& targetValues)
{
    // A convenience pointer to last layer in the neural network
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
    for (auto neuronIndex = 0u; neuronIndex < outputLayer.neuronCount() - 1; ++neuronIndex)
    {
        outputLayer.neurons[neuronIndex].calculateOutputGradients(targetValues[neuronIndex]);
    }

    // Calculate the gradients of the hidden layers
    for (auto layerIndex = layers.size() - 2; layerIndex > 0; --layerIndex)
    {
        // A convenience variable for the current hidden layer
        Layer &hiddenLayer = layers[layerIndex];

        // A convenience variable for the next layer relative to the current one
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
    for (auto layerIndex = layers.size() - 1; layerIndex > 0; --layerIndex)
    {
        // A convenience variable for the current hidden layer
        Layer &layer = layers[layerIndex];

        // A convenience variable for the next layer relative to the current one
        Layer &previousLayer = layers[layerIndex - 1];

        // Iterate over each neuron in the current later and tell the neuron to
        // update its input weights
        for (unsigned neuronIndex = 0; neuronIndex < layer.neuronCount() - 1; ++neuronIndex)
        {
            layer.neurons[neuronIndex].updateInputWeights(previousLayer);
        }
    }
}

void ArtificialNeuralNetwork::print() const
{
    cout << endl
         << endl
         << "Printing neural network:" << endl
         << endl;

    for (auto layerIndex = 0u; layerIndex < layers.size(); ++layerIndex)
    {
        cout << "Layer " << (layerIndex + 1) << endl;
        layers[layerIndex].print();
        cout << endl;
    }
    cout << endl;
}

void ArtificialNeuralNetwork::train(TrainingSet &trainingSet, const TrainingConfig& config)
{
    // Set learning parameters from config
    Neuron::setLearningRate(config.learningRate);
    Neuron::setMomentum(config.momentum);

    // Clear previous training history
    trainingHistory.clear();

    if (config.verbose)
    {
        cout << endl << "Training Neural Network" << endl;
    }

    auto inputLayerSize = layers[0].neuronCount();

    // Training loop over multiple epochs
    for (int epoch = 0; epoch < config.epochs; ++epoch)
    {
        // Iterate over training set
        for (auto recordIndex = 0; recordIndex < trainingSet.getNumberOfRows(); recordIndex++)
        {
            auto inputValues = trainingSet.getRecord(recordIndex);

            // Validate that the rows of the input vector to the Neural Network matches
            // the number of Neurons in the first layer (input Neurons) of the Neural Network
            if (inputValues.size() != inputLayerSize - 1)
            {
                cerr << endl
                     << "Error: The number of input values (" << inputValues.size()
                     << ") does not match the number of input neurons ("
                     << inputLayerSize - 1 << ") in the Neural Network."
                     << endl
                     << endl;
                exit(1);
            }

            // Assign (latch) input values to the Neurons of the input Layer
            for (auto i = 0u; i < inputValues.size(); i++)
            {
                layers[0].neurons[i].setOutputValue(inputValues[i]);
            }

            // Forward propagate input values
            // Skip the input layer because the output values for the input layer
            // have already been set
            for (auto layerIndex = 1u; layerIndex < layers.size(); ++layerIndex)
            {
                Layer &previousLayer = layers[layerIndex - 1];
                for (unsigned neuronIndex = 0; neuronIndex < layers[layerIndex].neuronCount(); ++neuronIndex)
                {
                    layers[layerIndex].neurons[neuronIndex].feedForward(previousLayer);
                }
            }

            // Back propagate with target values
            std::vector<double> targetValues;
            int label = trainingSet.getClassLabel(recordIndex); // Get class label
            
            // Convert class label to output format for the neural network
            // For binary classification with 1 output neuron
            if (layers.back().neuronCount() - 1 == 1)
            {
                targetValues.push_back(static_cast<double>(label));
            }
            else
            {
                // For multi-class with multiple output neurons
                for (unsigned i = 0; i < layers.back().neuronCount() - 1; ++i)
                {
                    targetValues.push_back(i == label ? 1.0 : 0.0);
                }
            }

            // Perform backpropagation to adjust weights
            this->backPropagate(targetValues);
        }

        // Store training history
        trainingHistory.push_back(this->error);

        // Print progress periodically
        if (config.verbose && config.printInterval > 0 && 
            (epoch % config.printInterval == 0 || epoch == config.epochs - 1))
        {
            cout << "Epoch " << epoch + 1 << "/" << config.epochs 
                 << " - Error: " << this->error << endl;
        }

        // Call progress callback if provided
        if (config.progressCallback)
        {
            config.progressCallback(epoch + 1, this->error);
        }

        // Call epoch callback if provided (allows early stopping)
        if (config.epochCallback)
        {
            bool continueTraining = config.epochCallback(epoch + 1, this->error);
            if (!continueTraining)
            {
                if (config.verbose)
                {
                    cout << "Training stopped early at epoch " << epoch + 1 << endl;
                }
                break;
            }
        }
    }

    if (config.verbose)
    {
        cout << endl
             << "Training complete - Final error: " << this->error << endl
             << endl;
    }
}

void ArtificialNeuralNetwork::feedForward(const std::vector<double>& inputValues)
{
    auto inputLayerSize = layers[0].neuronCount();

    // Validate input size
    if (inputValues.size() != inputLayerSize - 1)
    {
        cerr << endl
             << "Error: The number of input values (" << inputValues.size()
             << ") does not match the number of input neurons ("
             << inputLayerSize - 1 << ") in the Neural Network."
             << endl;
        exit(1);
    }

    // Assign input values to the input layer neurons
    for (auto i = 0u; i < inputValues.size(); i++)
    {
        layers[0].neurons[i].setOutputValue(inputValues[i]);
    }

    // Forward propagate through all layers
    for (auto layerIndex = 1u; layerIndex < layers.size(); ++layerIndex)
    {
        Layer &previousLayer = layers[layerIndex - 1];
        for (unsigned neuronIndex = 0; neuronIndex < layers[layerIndex].neuronCount(); ++neuronIndex)
        {
            layers[layerIndex].neurons[neuronIndex].feedForward(previousLayer);
        }
    }
}

void ArtificialNeuralNetwork::getResults(std::vector<double>& resultValues) const
{
    resultValues.clear();

    // Loops through all of the layers in the output layers
    for (unsigned neuronIndex = 0; neuronIndex < layers.back().neuronCount() - 1; ++neuronIndex)
    {
        resultValues.push_back(layers.back().neurons[neuronIndex].getOutputValue());
    }
}

Prediction ArtificialNeuralNetwork::predict(const std::vector<double>& inputValues)
{
    // Run forward propagation
    feedForward(inputValues);

    // Get output values
    std::vector<double> outputs;
    getResults(outputs);

    Prediction prediction;
    prediction.probabilities = outputs;

    // Determine class label and confidence
    if (outputs.size() == 1)
    {
        // Binary classification with single output neuron
        double value = outputs[0];
        prediction.classLabel = (value > 0.5) ? 1 : 0;
        prediction.confidence = (value > 0.5) ? value : (1.0 - value);
    }
    else
    {
        // Multi-class classification
        auto maxIt = std::max_element(outputs.begin(), outputs.end());
        prediction.classLabel = std::distance(outputs.begin(), maxIt);
        prediction.confidence = *maxIt;
    }

    return prediction;
}

std::vector<Prediction> ArtificialNeuralNetwork::predictBatch(const std::vector<std::vector<double>>& inputs)
{
    std::vector<Prediction> predictions;
    predictions.reserve(inputs.size());

    for (const auto& input : inputs)
    {
        predictions.push_back(predict(input));
    }

    return predictions;
}

double ArtificialNeuralNetwork::getError() const
{
    return error;
}

std::vector<double> ArtificialNeuralNetwork::getTrainingHistory() const
{
    return trainingHistory;
}

void ArtificialNeuralNetwork::save(const std::string& filepath) const
{
    std::ofstream outFile(filepath);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file for writing: " << filepath << endl;
        return;
    }

    // Save topology
    outFile << layers.size() << endl;
    for (const auto& layer : layers)
    {
        outFile << (layer.neuronCount() - 1) << " "; // Exclude bias neuron
    }
    outFile << endl;

    // Save weights for each layer
    for (size_t layerIndex = 0; layerIndex < layers.size() - 1; ++layerIndex)
    {
        const Layer& layer = layers[layerIndex];
        for (size_t neuronIndex = 0; neuronIndex < layer.neuronCount(); ++neuronIndex)
        {
            const auto& neuron = layer.neurons[neuronIndex];
            // Access connections through reflection or friend class would be needed
            // For now, we'll note this limitation
            outFile << "# Layer " << layerIndex << " Neuron " << neuronIndex << " weights" << endl;
        }
    }

    outFile.close();
}

void ArtificialNeuralNetwork::load(const std::string& filepath)
{
    std::ifstream inFile(filepath);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file for reading: " << filepath << endl;
        return;
    }

    // Load topology
    size_t numLayers;
    inFile >> numLayers;

    std::vector<unsigned> topology;
    for (size_t i = 0; i < numLayers; ++i)
    {
        unsigned layerSize;
        inFile >> layerSize;
        topology.push_back(layerSize);
    }

    // Reconstruct network with loaded topology
    layers.clear();
    unsigned int numberOfOutputs = 0;
    for (auto layerIndex = 0u; layerIndex < topology.size(); ++layerIndex)
    {
        auto layerSize = topology[layerIndex];
        numberOfOutputs = layerIndex < (topology.size() - 1) ? topology[layerIndex + 1] : 0;
        layers.push_back(Layer(layerSize, layerIndex, numberOfOutputs));
    }

    // Load weights (implementation would require access to connection weights)
    // For now, this is a placeholder

    inFile.close();
}

} // namespace ann
