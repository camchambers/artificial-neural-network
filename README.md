# C++ Artificial Neural Network (ANN)

> A simple object-oriented artificial neural network (ANN) built in C++
## Example (Optional)

```cpp

    // Create a vector that defines the network topology (layers and nodes per layer)
    vector<unsigned> topology = {4, 6, 3, 2};

    // Instantiate a new artificial neural network object
    ArtificialNeuralNetwork ann(topology);

    // Define input to the artificial neural network
    vector<double> inputVals = {2.24, 6, 41, 7.48};

    // Train the neural network
    ann.train(inputVals);

    // Print neural network contents
    ann.print();

```

---
### Clone

- Clone this repo to your local machine using `git@github.com:camchambers/ann.git`
