#include "Connection.h"
#include <iostream>
#include <random>

using namespace std;

namespace ann {

// Helper function to get a thread-safe random number generator
// Using static local variables ensures initialization happens on first use
static mt19937& getRandomGenerator()
{
    static random_device rd; // hardware entropy
    static mt19937 gen(rd()); // random number engine
    return gen;
}

Connection::Connection()
{
    static uniform_real_distribution<double> dis(-1.0, 1.0); // distribution
    weight = dis(getRandomGenerator());
}

void Connection::print() const
{
    cout << weight;
}

} // namespace ann
