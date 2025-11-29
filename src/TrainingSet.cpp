#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "ann/TrainingSet.h"

using namespace std;

namespace ann {

TrainingSet::TrainingSet() : numberOfRows(0), numberOfColumns(0)
{
}

int TrainingSet::getNumberOfRows() const
{
    return this->numberOfRows;
}

int TrainingSet::getNumberOfColumns() const
{
    return this->numberOfColumns;
}

void TrainingSet::read(std::string fileName)
{
    // Get data set dimensions
    this->getDimensions(fileName);

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
}

vector<double> TrainingSet::getRecord(int index) const
{
    if (index > this->numberOfRows)
    {
        cout << "Error: invalid training set index";
        exit(1);
    }
    return this->trainingData[index];
}

int TrainingSet::getClassLabel(int index) const
{
    if (index > this->numberOfRows)
    {
        cout << "Error: invalid training set index";
        exit(1);
    }
    return this->classLabels[index];
}

void TrainingSet::getDimensions(std::string fileName)
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

void TrainingSet::print()
{
    for (auto x = 0; x < this->numberOfRows; x++)
    {
        for (auto y = 0; y < this->numberOfColumns - 1; y++)
        {
            cout << this->trainingData[x][y];

            if (y != this->numberOfColumns - 2)
            {
                cout << ", ";
            }
        }
        cout << " = " << this->classLabels[x] << endl;
    }
    cout << endl;
}

void TrainingSet::scale()
{
    // Min-Max normalization to scale features to [0, 1] range
    int numFeatures = this->numberOfColumns - 1;
    
    for (int featureIndex = 0; featureIndex < numFeatures; ++featureIndex)
    {
        // Find min and max for this feature
        double minVal = this->trainingData[0][featureIndex];
        double maxVal = this->trainingData[0][featureIndex];
        
        for (int rowIndex = 1; rowIndex < this->numberOfRows; ++rowIndex)
        {
            double value = this->trainingData[rowIndex][featureIndex];
            if (value < minVal) minVal = value;
            if (value > maxVal) maxVal = value;
        }
        
        // Scale feature if range is non-zero
        double range = maxVal - minVal;
        if (range > 0.0001) // Avoid division by zero
        {
            for (int rowIndex = 0; rowIndex < this->numberOfRows; ++rowIndex)
            {
                this->trainingData[rowIndex][featureIndex] = 
                    (this->trainingData[rowIndex][featureIndex] - minVal) / range;
            }
        }
    }
}

} // namespace ann
