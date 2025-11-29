#pragma once
#include <vector>
#include <string>

namespace ann {

/**
 * @brief Manages training data for neural network training
 * 
 * This class handles reading, storing, and accessing training data from CSV files.
 * The CSV format should have feature values followed by a class label in the last column.
 * 
 * Example CSV format:
 * @code
 * 0.0,0.0,0
 * 0.0,1.0,1
 * 1.0,0.0,1
 * 1.0,1.0,0
 * @endcode
 */
class TrainingSet
{
public:
    /**
     * @brief Default constructor
     * 
     * Initializes an empty training set with zero rows and columns.
     */
    TrainingSet();

    /**
     * @brief Reads a training set from a CSV file
     * 
     * @param filename Path to the CSV file to read
     * 
     * The CSV file should have one sample per line, with features separated by commas.
     * The last column should be the class label (integer).
     */
    void read(std::string filename);

    /**
     * @brief Print the training data to console
     * 
     * Prints all samples with their features and class labels.
     * Useful for debugging and data verification.
     */
    void print();

    /**
     * @brief Get a specific record from the training set
     * 
     * @param index Zero-based index of the record to retrieve
     * @return Vector of feature values for the specified record
     */
    std::vector<double> getRecord(int index) const;

    /**
     * @brief Get the class label for a specific record
     * 
     * @param index Zero-based index of the record
     * @return The class label (integer) for the specified record
     */
    int getClassLabel(int index) const;

    /**
     * @brief Scale/normalize the training data
     * 
     * Applies min-max normalization to scale all features to the [0, 1] range.
     * This ensures that all features are weighted equally during training and
     * can improve training performance and convergence.
     * 
     * Should be called after reading the data and before training.
     */
    void scale();

    /**
     * @brief Get the total number of samples in the dataset
     * 
     * @return Number of training samples
     */
    int getNumberOfRows() const;

    /**
     * @brief Get the total number of columns (features + label)
     * 
     * @return Number of columns in the dataset
     */
    int getNumberOfColumns() const;

private:
    /**
     * @brief Determine dataset dimensions from file
     * 
     * @param fileName Path to the CSV file
     * 
     * Internal method to read file and determine rows and columns.
     */
    void getDimensions(std::string fileName);

    /**
     * @brief The parsed training data (features only)
     */
    std::vector<std::vector<double>> trainingData;

    /**
     * @brief Parsed class labels
     */
    std::vector<int> classLabels;

    /**
     * @brief Number of training samples
     */
    int numberOfRows;

    /**
     * @brief Number of columns (features + label)
     */
    int numberOfColumns;
};

} // namespace ann
