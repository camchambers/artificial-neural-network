#pragma once

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
    Connection();

    // The weight of a connection between neurons
    double weight;

    // The change in the weight between epochs
    double deltaWeight;

    /**
     * @brief Prints the weight of a Connection
     * 
     * @param connectionIndex 
     */
    void print();
};