#pragma once

#include <functional>

namespace ann {

/**
 * @brief Configuration parameters for training a neural network
 * 
 * This struct provides flexible configuration options for the training process,
 * allowing users to customize learning parameters and monitor progress.
 * 
 * Example usage:
 * @code
 * TrainingConfig config;
 * config.epochs = 2000;
 * config.learningRate = 0.2;
 * config.verbose = true;
 * config.progressCallback = [](int epoch, double error) {
 *     std::cout << "Epoch " << epoch << ": error = " << error << std::endl;
 * };
 * ann.train(trainingSet, config);
 * @endcode
 */
struct TrainingConfig {
    /**
     * @brief Number of training epochs (complete passes through the dataset)
     */
    int epochs = 1000;

    /**
     * @brief How often to report progress (in epochs)
     * 
     * Progress will be reported every printInterval epochs.
     * Set to 0 to disable periodic reporting.
     */
    int printInterval = 200;

    /**
     * @brief Learning rate for weight updates
     * 
     * Controls how much weights are adjusted during training.
     * Typical values: 0.01 to 0.3
     */
    double learningRate = 0.15;

    /**
     * @brief Momentum value for weight updates
     * 
     * Helps accelerate training and avoid local minima.
     * Typical values: 0.5 to 0.9
     */
    double momentum = 0.5;

    /**
     * @brief Enable verbose output during training
     * 
     * When true, training progress will be printed to console.
     */
    bool verbose = false;

    /**
     * @brief Optional callback for monitoring training progress
     * 
     * Called periodically during training with the current epoch number
     * and error value. Allows custom progress monitoring and logging.
     * 
     * Example:
     * @code
     * config.progressCallback = [](int epoch, double error) {
     *     if (epoch % 100 == 0) {
     *         myLogger.log("Training progress: " + std::to_string(error));
     *     }
     * };
     * @endcode
     */
    std::function<void(int epoch, double error)> progressCallback;

    /**
     * @brief Optional callback called at the end of each epoch
     * 
     * Called after each complete pass through the training data.
     * Useful for implementing custom learning rate schedules, early stopping,
     * or other epoch-based logic.
     * 
     * Return false to stop training early, true to continue.
     * 
     * Example:
     * @code
     * config.epochCallback = [](int epoch, double error) {
     *     // Early stopping if error is low enough
     *     return error > 0.001;
     * };
     * @endcode
     */
    std::function<bool(int epoch, double error)> epochCallback;
};

} // namespace ann
