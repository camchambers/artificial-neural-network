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

```cpp
    TrainingSet trainingSet;
    trainingSet.read("train.csv");
    ann.train(trainingSet);
```

The Artificial Neural Network class also has the capability to print the contents of the network (the weights and values for each node in every layer). 

```cppp
    ann.print();
```

## Project Structure

```
ANN/
├── Main.cpp                          # Main program entry point
├── ArtificialNeuralNetwork.cpp/h     # Core neural network implementation
├── Layer.cpp/h                       # Layer management
├── Neuron.cpp/h                      # Individual neuron logic
├── Connection.cpp/h                  # Neuron connections and weights
├── TrainingSet.cpp/h                 # Training data handling
├── CMakeLists.txt                    # CMake build configuration
├── tests/
│   ├── test_ann.cpp                  # Catch2 unit tests
│   ├── catch.hpp                     # Catch2 framework header
│   └── README.md                     # Testing documentation
└── build/                            # Build artifacts (generated)
    └── bin/
        ├── ann                       # Main executable
        └── test_ann                  # Test executable
```

## Compilation

### Prerequisites

**CMake** (for CMake build method):
```bash
# Ubuntu/Debian
sudo apt install cmake

# Or using Snap (if apt repositories unavailable)
sudo snap install cmake --classic

# Verify installation
cmake --version
```

**G++** compiler with C++17 support (included in most modern Linux distributions)

### Using CMake (Recommended)
```bash
# 1. Navigate into the ANN directory
cd ANN

# 2. Create a build directory
mkdir build && cd build

# 3. Configure the project
cmake ..

# 4. Build the project
cmake --build .

# 5. Run the program
./bin/ann

# 6. Run tests
./bin/test_ann
# or use CTest
ctest
```

### Using G++
```bash
# 1. Navigate into the ANN directory
cd ANN

# 2. Compile the main executable
g++ -std=c++17 -o ann Main.cpp ArtificialNeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp TrainingSet.cpp

# 3. Run the program
./ann
```

## Testing

The project includes a comprehensive test suite using [Catch2](https://github.com/catchorg/Catch2), a modern C++ testing framework.

### Running Tests

**With CMake (Recommended):**
```bash
cd ANN/build
ctest                    # Run all tests via CTest
ctest --verbose          # Verbose output
./bin/test_ann           # Run tests directly with Catch2
```

**With G++:**
```bash
cd ANN
g++ -std=c++17 -o tests/test_ann tests/test_ann.cpp ArtificialNeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp TrainingSet.cpp
./tests/test_ann
```

### Test Features

- **15 test cases** covering all major components
- **Tag-based filtering**: Run specific test categories
  ```bash
  ./bin/test_ann "[Connection]"   # Connection tests only
  ./bin/test_ann "[Neuron]"       # Neuron tests only
  ./bin/test_ann "[ANN]"          # ANN tests only
  ```
- **Detailed output**: Use `--success` flag for verbose assertions
- See `ANN/tests/README.md` for more details

### Using Visual Studio
1. Make sure [CMake support for C++](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio) is installed in your version of Visual Studio
2. Open Visual Studio
3. Select "Open a local folder"
4. Select the ANN folder within the project
5. Visual Studio will automatically detect the CMakeLists.txt and configure the project
6. Select *Build* from the menu and then *Build all*
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
