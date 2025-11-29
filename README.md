# Artificial Neural Network

![Tests](https://github.com/camchambers/artificial-neural-network/workflows/Tests/badge.svg)

A flexible, reusable C++ library for creating and training artificial neural networks. 

[Artificial Neural Networks](https://en.wikipedia.org/wiki/Artificial_neural_network) (ANNs) are biologically inspired models of human central nervous system activity [[1]](#footnote_1)[[2]](#footnote_2) commonly used for classification and regression [[3]](#footnote_3) in the field of [Machine Learning](https://en.wikipedia.org/wiki/Machine_learning).

## Features

- **Flexible Network Topology**: Define custom layer structures
- **Configurable Training**: Customize learning rate, momentum, epochs, and more
- **Progress Monitoring**: Built-in callbacks for tracking training progress
- **Easy Predictions**: Simple API for making predictions with confidence scores
- **Model Persistence**: Save and load trained models (coming soon)
- **Training History**: Track error over epochs

## Quick Start

### Building with G++

```bash
# Compile the library and example
g++ -std=c++17 -I./include -I./src -o xor_example \
    examples/xor_classification.cpp \
    src/ArtificialNeuralNetwork.cpp \
    src/Layer.cpp \
    src/Neuron.cpp \
    src/Connection.cpp \
    src/TrainingSet.cpp

# Run the example
cd examples && ../xor_example
```

### Building with CMake

```bash
mkdir build && cd build
cmake ..
make

# Run the example
./xor_classification

# Run tests
./test_ann
# or use CTest
ctest
```

## Usage

```cpp
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingSet.h"
#include "ann/TrainingConfig.h"

using namespace ann;

int main() {
    // Create network: 2 inputs, 4 hidden neurons, 1 output
    std::vector<unsigned> topology = {2, 4, 1};
    ArtificialNeuralNetwork network(topology);
    
    // Load training data
    TrainingSet trainingData;
    trainingData.read("train.csv");
    
    // Configure training
    TrainingConfig config;
    config.epochs = 1000;
    config.learningRate = 0.15;
    config.momentum = 0.5;
    config.verbose = true;
    config.progressCallback = [](int epoch, double error) {
        // Custom progress monitoring
        if (epoch % 100 == 0) {
            std::cout << "Progress: " << epoch << " - " << error << std::endl;
        }
    };
    
    // Train the network
    network.train(trainingData, config);
    
    // Make predictions
    auto prediction = network.predict({0.5, 0.8});
    std::cout << "Predicted class: " << prediction.classLabel << std::endl;
    std::cout << "Confidence: " << prediction.confidence << std::endl;
    
    return 0;
}
```

## Project Structure

```
artificial-neural-network/
├── include/ann/                    # Public API headers
│   ├── ArtificialNeuralNetwork.h   # Main network class
│   ├── TrainingSet.h               # Training data management
│   └── TrainingConfig.h            # Training configuration
├── src/                            # Implementation files (private)
│   ├── ArtificialNeuralNetwork.cpp
│   ├── Layer.h / Layer.cpp
│   ├── Neuron.h / Neuron.cpp
│   ├── Connection.h / Connection.cpp
│   └── TrainingSet.cpp
├── examples/                       # Example programs
│   ├── xor_classification.cpp
│   └── train.csv
├── tests/                          # Unit tests
│   ├── test_ann.cpp                # Catch2 unit tests
│   ├── catch.hpp                   # Catch2 framework header
│   └── README.md                   # Testing documentation
└── CMakeLists.txt                  # Build configuration
```

## API Reference

### ArtificialNeuralNetwork

```cpp
// Constructor
ArtificialNeuralNetwork(const std::vector<unsigned>& topology);

// Training
void train(TrainingSet& trainingSet, const TrainingConfig& config = TrainingConfig());

// Prediction
Prediction predict(const std::vector<double>& inputValues);
std::vector<Prediction> predictBatch(const std::vector<std::vector<double>>& inputs);

// Model inspection
double getError() const;
std::vector<double> getTrainingHistory() const;

// Model persistence
void save(const std::string& filepath) const;  // Coming soon
void load(const std::string& filepath);        // Coming soon
```

### TrainingConfig

```cpp
struct TrainingConfig {
    int epochs = 1000;                    // Number of training epochs
    int printInterval = 200;              // Progress reporting interval
    double learningRate = 0.15;           // Learning rate
    double momentum = 0.5;                // Momentum value
    bool verbose = false;                 // Enable console output
    
    // Callbacks
    std::function<void(int epoch, double error)> progressCallback;
    std::function<bool(int epoch, double error)> epochCallback;
};
```

### Prediction

```cpp
struct Prediction {
    int classLabel;                       // Predicted class
    double confidence;                    // Confidence score (0.0 to 1.0)
    std::vector<double> probabilities;    // Raw output values
};
```

### TrainingSet

```cpp
// Load data from CSV
void read(std::string filename);

// Normalize features to [0, 1] range
void scale();

// Access data
std::vector<double> getRecord(int index) const;
int getClassLabel(int index) const;
int getNumberOfRows() const;
```

## Training Data Format

The library expects CSV files with features followed by a class label:

```csv
0.0,0.0,0
0.0,1.0,1
1.0,0.0,1
1.0,1.0,0
```

## Advanced Features

### Custom Progress Monitoring

```cpp
TrainingConfig config;
config.progressCallback = [](int epoch, double error) {
    if (error < 0.001) {
        std::cout << "Low error achieved at epoch " << epoch << std::endl;
    }
};
```

### Early Stopping

```cpp
TrainingConfig config;
config.epochCallback = [](int epoch, double error) {
    // Stop training if error is below threshold
    return error > 0.001;  // Return false to stop
};
```

### Batch Predictions

```cpp
std::vector<std::vector<double>> inputs = {
    {0.0, 0.0},
    {0.0, 1.0},
    {1.0, 0.0},
    {1.0, 1.0}
};

auto predictions = network.predictBatch(inputs);
for (const auto& pred : predictions) {
    std::cout << "Class: " << pred.classLabel 
              << " Confidence: " << pred.confidence << std::endl;
}
```

## Namespace

All library classes are in the `ann` namespace:

```cpp
using namespace ann;
// or
ann::ArtificialNeuralNetwork network(topology);
```

## Testing

The project includes a comprehensive test suite using [Catch2](https://github.com/catchorg/Catch2), a modern C++ testing framework.

### Running Tests

**With CMake (Recommended):**
```bash
cd build
ctest                    # Run all tests via CTest
ctest --verbose          # Verbose output
./test_ann               # Run tests directly with Catch2
```

**With G++:**
```bash
g++ -std=c++17 -I./include -I./src -o test_ann tests/test_ann.cpp src/*.cpp
./test_ann
```

### Test Features

- **14 test cases** covering all major components
- **Tag-based filtering**: Run specific test categories
  ```bash
  ./test_ann "[Connection]"   # Connection tests only
  ./test_ann "[Neuron]"       # Neuron tests only
  ./test_ann "[ANN]"          # ANN tests only
  ```
- **Detailed output**: Use `--success` flag for verbose assertions
- See `tests/README.md` for more details

## FAQ

**Many machine learning libraries exist with Artificial Neural Network implementations. Why reinvent the wheel?**

Building a solution from scratch allows for mastery (a deep understanding of how all of the pieces of a solution work) and creativity (extending or changing how a solution behaves).

## Clone

Clone this repo to your local machine using `git@github.com:camchambers/artificial-neural-network.git`

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

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
