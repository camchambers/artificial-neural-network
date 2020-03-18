# Artificial Neural Network
> An [Artificial Neural Network](https://en.wikipedia.org/wiki/Artificial_neural_network) (ANN) is a [Machine Learning](https://en.wikipedia.org/wiki/Machine_learning) algorithm used for pattern recognition (classification) and regression. 

### TO DO

- [x] Write classes for neural network components
- [x] Complete code for constructing network topology
- [x] Seperate classes into discrete files
- [x] Add bias nodes automatically while constructing the network
- [x] Complete a functioning neural network
- [x] Write a function for reading training data from a CSV
- [ ] Add the ability to evaluate a test set 
- [ ] Write a function for reading test data from a CSV
- [ ] Write a program to scale training and test data
- [ ] Add the ability to support multiple activation functions

## Example

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
## FAQ
**Many machine learning libraries exist with Artifical Nerual Network implementations. Why reinvent the wheel?**

Building a solution from scratch allows for mastery (a deep understanding of how all of the pieces of a solution work) and creativity (extending or changing how a solution behaves). 

---
### Clone

- Clone this repo to your local machine using `git@github.com:camchambers/ann.git`

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © <a href="https://www.camchambers.com" target="_blank">Cam Chambers</a>.
