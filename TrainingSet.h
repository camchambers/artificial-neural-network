#pragma once
#include <vector>
using namespace std;

class TrainingSet
{
public:
    /**
     * @brief Reads a training set from a CSV file into a vector of instances
     * 
     * @param filename the relative path to the csv file to be read
     */
    void read(string filename);

    /**
     * @brief The number of records in the CSV file that has been read
     * 
     * @return int 
     */
    int recordCount();

    /**
     * @brief Gets a particular record from the training set given an index
     * 
     * @param index The index of the record to read
     * @return vector<double> 
     */
    vector<double> getRecord(int index);

    /**
     * @brief Scales training data to ensure attributes are weighted equally
     * 
     */
    void scale();

    /**
     * @brief Determines the dimensions of a dataset (rows and columns)
     * 
     * @param fileName The name of the file
     * @return vector<double> A vector of dimensions
     */
    void getDimensions(string fileName);

    /**
     * @brief Gets the number of records from a a data set 
     * 
     */
    int getNumberOfRows();

    /**
     * @brief Gets the number of columns from a a data set 
     * 
     */
    int getNumberOfColumns();

private:
    /**
     * @brief The parsed training data read from the CSV file
     * 
     */
    vector<vector<double>> trainingData;

    /**
     * @brief Parsed class labels read from the CSV file
     * 
     */
    vector<int> classLabels;

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