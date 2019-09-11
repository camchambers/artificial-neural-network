#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TrainingSet.h"

using namespace std;

int TrainingSet::getNumberOfRows()
{
    return this->numberOfRows;
}

int TrainingSet::getNumberOfColumns()
{
    return this->numberOfColumns;
}

// Reads a file to create a training set
// TODO Have the read function parse number of elements in the line -1 and create another function for parsing out the last element of each line (class label)
void TrainingSet::read(string fileName)
{

    // Get data set dimensions
    this->getDimensions(fileName);

    // Temporary variable to store the parsed dataset
    vector<vector<double>> data;

    // Input stream reader for reading the file
    ifstream inputFile(fileName);

    // Parse the input file
    while (inputFile)
    {
        string line;

        // Exit if there are no more lines to read
        if (!getline(inputFile, line))
        {
            break;
        }

        stringstream stringStream(line);

        vector<double> record;

        string substring;

        for (int columns = 0; columns <= this->numberOfColumns - 2; columns++)
        {
            // A vector of parsed elements from the line

            getline(stringStream, substring, ',');

            // Convert the string to a double
            double convertedValue = stod(substring);

            // Append the value to our record vector
            record.push_back(convertedValue);
        }

        // Push the record onto the training data vector
        this->trainingData.push_back(record);

        // Retrieve the class label
        getline(stringStream, substring, ',');
        this->classLabels.push_back(stoi(substring));
    }

    // Close the file connection
    inputFile.close();
};

// Gets a record from the training set given a record index
vector<double> TrainingSet::getRecord(int index)
{
    if (index > this->numberOfRows)
    {
        cout << "Error: invalid training set index";
        exit(1);
    }
    return this->trainingData[index];
}

void TrainingSet::getDimensions(string fileName)
{

    int numberOfColumns = 0;
    int numberOfRows = 0;

    // Input stream reader for reading the file
    ifstream inputFile(fileName);

    // Temporary variable for reading a line
    string line;

    // Determine the number of columns using the first line
    getline(inputFile, line);

    // Increment the number of rows since we read the first line
    numberOfRows++;

    // Stream object for the current line
    stringstream stringStream(line);

    // Determine number of columns using the first line
    while (stringStream.good())
    {
        numberOfColumns++;

        // A vector of parsed elements from the line
        string substring;

        getline(stringStream, substring, ',');
        // Convert the string to a double
    }

    // Determine number of rows
    while (inputFile)
    {
        // Exit if there are no more lines to read
        if (!getline(inputFile, line))
        {
            break;
        }
        numberOfRows++;
    }

    // Close the file connection
    inputFile.close();

    this->numberOfColumns = numberOfColumns;
    this->numberOfRows = numberOfRows;
}
