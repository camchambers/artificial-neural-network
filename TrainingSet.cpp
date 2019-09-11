#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TrainingSet.h"

using namespace std;

// Return the number of records read by the training set
int TrainingSet::recordCount()
{
    return this->numberOfRecords;
}

// Reads a file to create a training set
// TODO Have the read function parse number of elements in the line -1 and create another function for parsing out the last element of each line (class label)
void TrainingSet::read(string fileName)
{
    // Temporary variable to store the parsed dataset
    vector<vector<double>> data;

    // Input stream reader for reading the file
    ifstream inputFile(fileName);

    // Keep track of lines being parsed
    int lineNumber = 0;

    // Parse the input file
    while (inputFile)
    {
        lineNumber++;
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
