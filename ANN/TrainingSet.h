#pragma once
#include <vector>
#include <string>

class TrainingSet
{
public:
    /**
     * @brief Reads a training set from a CSV file into a vector of instances
     * 
     * @param filename the relative path to the csv file to be read
     */
    void read(std::string filename);

    /**
     * @brief Prints the training data
     * 
     */
    void print();

    /**
     * @brief Gets a particular record from the training set given an index
     * 
     * @param index The index of the record to read
     * @return std::vector<double> 
     */
    std::vector<double> getRecord(int index) const;

    /**
     * @brief Scales training data to ensure attributes are weighted equally
     * 
     */
    void scale();

    /**
     * @brief Determines the dimensions of a dataset (rows and columns)
     * 
     * @param fileName The name of the file
     * @return std::vector<double> A vector of dimensions
     */
    void getDimensions(std::string fileName);

    /**
     * @brief Gets the number of records from a a data set 
     * 
     */
    int getNumberOfRows() const;

    /**
     * @brief Gets the number of columns from a a data set 
     * 
     */
    int getNumberOfColumns() const;

private:
    /**
     * @brief The parsed training data read from the CSV file
     * 
     */
    std::vector<std::vector<double>> trainingData;

    /**
     * @brief Parsed class labels read from the CSV file
     * 
     */
    std::vector<int> classLabels;

    /**
     * @brief The number of records read from the training set file
     * 
     */
    int numberOfRows;

    /**
     * @brief The number of columns in the data set training set training file
     * 
     */
    int numberOfColumns;
};