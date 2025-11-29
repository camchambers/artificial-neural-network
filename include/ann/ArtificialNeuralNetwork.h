#pragma once

#include <vector>
#include <string>
#include "TrainingConfig.h"

namespace ann {

// Forward declarations
class Layer;
class TrainingSet;

/**
 * @brief Prediction result with class label and confidence
 */
struct Prediction {
    /**
     * @brief The predicted class label
     */
    int classLabel;

    /**
     * @brief Confidence score for the prediction (0.0 to 1.0)
     */
    double confidence;

    /**
     * @brief Raw output values from all output neurons
     */
    std::vector<double> probabilities;
};

/**
 * @brief Artificial Neural Network for classification and regression
 * 
 * This class implements a feedforward neural network with backpropagation
 * learning algorithm. It supports flexible configuration, model persistence,
 * and comprehensive prediction capabilities.
 * 
 * Example usage:
 * @code
 * // Create a network with 2 inputs, 4 hidden neurons, 1 output
 * std::vector<unsigned> topology = {2, 4, 1};
 * ann::ArtificialNeuralNetwork network(topology);
 * 
 * // Configure training
 * ann::TrainingConfig config;
 * config.epochs = 1000;
 * config.learningRate = 0.15;
 * config.verbose = true;
 * 
 * // Train the network
 * ann::TrainingSet trainingData;
 * trainingData.read("train.csv");
 * network.train(trainingData, config);
 * 
 * // Make predictions
 * auto prediction = network.predict({0.5, 0.8});
 * std::cout << "Predicted class: " << prediction.classLabel << std::endl;
 * 
 * // Save the trained model
 * network.save("model.ann");
 * @endcode
 */
class ArtificialNeuralNetwork
{
public:
    /**
     * @brief Construct a new Artificial Neural Network object
     * 
     * @param topology The topology (number of neurons in each layer) of the neural network.
     *                 The first element is the input layer size, the last element is the
     *                 output layer size, and intermediate elements are hidden layer sizes.
     * 
     * Example: {2, 4, 1} creates a network with 2 inputs, 4 hidden neurons, and 1 output.
     */
    ArtificialNeuralNetwork(const std::vector<unsigned> &topology);

    /**
     * @brief Destructor
     */
    ~ArtificialNeuralNetwork();

    /**
     * @brief Trains the neural network using backpropagation
     * 
     * @param trainingSet The dataset to train on
     * @param config Training configuration parameters (epochs, learning rate, callbacks, etc.)
     * 
     * The training process iterates through the dataset multiple times (epochs),
     * adjusting weights to minimize prediction error. Progress can be monitored
     * through callbacks in the config parameter.
     */
    void train(TrainingSet &trainingSet, const TrainingConfig& config = TrainingConfig());

    /**
     * @brief Feed forward input values through the network
     * 
     * @param inputValues The input values to process. Must match the input layer size.
     * 
     * This method propagates the input through all layers of the network,
     * computing the final output. Use getResults() to retrieve the output.
     */
    void feedForward(const std::vector<double>& inputValues);

    /**
     * @brief Make a prediction for a single input
     * 
     * @param inputValues The input values to predict on
     * @return Prediction struct containing class label, confidence, and probabilities
     * 
     * For binary classification (1 output neuron), returns 0 or 1 with confidence.
     * For multi-class (N output neurons), returns the class with highest probability.
     */
    Prediction predict(const std::vector<double>& inputValues);

    /**
     * @brief Make predictions for multiple inputs (batch prediction)
     * 
     * @param inputs Vector of input vectors to predict on
     * @return Vector of predictions, one for each input
     * 
     * More efficient than calling predict() multiple times.
     */
    std::vector<Prediction> predictBatch(const std::vector<std::vector<double>>& inputs);

    /**
     * @brief Get the raw output values from the network
     * 
     * @param resultValues Output parameter to store the results
     * 
     * Returns the output values from all neurons in the output layer.
     */
    void getResults(std::vector<double>& resultValues) const;

    /**
     * @brief Get the current error/loss value
     * 
     * @return The current root mean square error
     */
    double getError() const;

    /**
     * @brief Get the complete training history
     * 
     * @return Vector of error values, one per epoch
     * 
     * Only populated if training was performed. Empty if no training has occurred.
     */
    std::vector<double> getTrainingHistory() const;

    /**
     * @brief Save the trained model to a file
     * 
     * @param filepath Path to save the model
     * 
     * Saves the network topology and all learned weights to a file.
     * The model can be loaded later using load().
     */
    void save(const std::string& filepath) const;

    /**
     * @brief Load a trained model from a file
     * 
     * @param filepath Path to the saved model file
     * 
     * Loads a previously saved model, restoring the topology and weights.
     * The current network structure will be replaced.
     */
    void load(const std::string& filepath);

    /**
     * @brief Print the network structure and weights
     * 
     * Prints detailed information about all layers, neurons, and connections.
     * Useful for debugging and understanding the network structure.
     */
    void print() const;

private:
    /**
     * @brief Back propagate errors through the network
     * 
     * @param targetValues Expected output values for the current input
     * 
     * Calculates gradients and updates weights to minimize error.
     */
    void backPropagate(const std::vector<double>& targetValues);

    std::vector<Layer> layers;
    double error;
    std::vector<double> trainingHistory;
};

} // namespace ann
