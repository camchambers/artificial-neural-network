#include "Connection.h"
#include <iostream>

using namespace std;

Connection::Connection()
{
    weight = (double)rand() / RAND_MAX * 2.0 - 1.0;
}

void Connection::print()
{
    cout << weight;
}