# Artificial Neural Network
>[Artificial Neural Networks](https://en.wikipedia.org/wiki/Artificial_neural_network) (ANNs) are biologically inspired models of human central nervous system activity [[1]](#footnote_1)[[2]](#footnote_2) commonly used for classification and regression [[3]](#footnote_3) in the field of [Machine Learning](https://en.wikipedia.org/wiki/Machine_learning). The following project is a basic implementation of an artificial neural network written in C++. 


## Usage

Using this project, an ANN can be customized to classify a dataset as follows: 

1. Define a network topology as a vector that specifies the number of layers (number of elements in the vector) and nodes per layer (numeric values contained in the vector). Typically, the input layer (first element in the vector) matches the number of variables in our classification problem, and the output layer matches the number of class labels (ie. true and false for a binary classification problem). 

```cpp
    vector<unsigned> topology = {4, 6, 3, 2};
```
2. Instantiate a new artificial neural network object and pass in the topology to the constructor.
```cpp
    ArtificialNeuralNetwork ann(topology);
```

3. Train the neural network using a training set. Here, the ANN learns underlying relationships within the data and is able to infer classification patterns. The training set must be a CSV file with the class label as the last element. 

```cppp
    ann.train("train.csv");
```

4. Use the trained model to classify new data 

```cppp
    ann.test("test.csv");
```

The Artificial Neural Network class also has the capability to print the contents of the network (the weights and values for each node in every layer). 

```cppp
    ann.print();
```

## Compilation

### Using CMake
```bash
# 1. Create a build directory within the project folder
mkdir build

# 2. Navigate into the build directory
cd build

# 3.  Run cmake - targeting the parent directory
cmake ..

# 4. Finish building the program with make
make
```

### Using G++
```bash

# 1. Navigate into the project directory
cd artificial-neural-network

# 2. Compile the executable
g++ -std=c++11 -o ann *.cpp
```

### Using Visual Studio
1. Make sure [C++ support](https://docs.microsoft.com/en-us/cpp) is installed in your version of Visual Studio
2. Open Visual Studio
3. Select "Open a local folder"
4. Select the project ("artificial-neural-network")
5. Select *Build* from the menu and then *Build all*
6. Select *ann.exe* from the run button drop down
7. Run the project using the run button

## FAQ
**Many machine learning libraries exist with Artifical Nerual Network implementations. Why reinvent the wheel?**

Building a solution from scratch allows for mastery (a deep understanding of how all of the pieces of a solution work) and creativity (extending or changing how a solution behaves). 

---
## Clone

- Clone this repo to your local machine using `git@github.com:camchambers/ann.git`

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © <a href="https://www.camchambers.com" target="_blank">Cam Chambers</a>.

## References
<a name="footnote_1">[1]</a> Warren S McCulloch and Walter Pitts. A logical calculus of the ideas immanent
in nervous activity. The bulletin of mathematical biophysics, 5(4):115–133, 1943.

<a name="footnote_2">[2]</a> John J Hopfield and David W Tank. Computing with neural circuits: A model.
Science, 233(4764):625–633, 1986.

<a name="footnote_3">[2]</a> Pang-Ning Tan, Michael Steinbach, and Vipin Kumar. Introduction to data
mining. 1st. Boston: Pearson Addison Wesley. xxi, 2018.
