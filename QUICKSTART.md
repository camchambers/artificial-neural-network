# Quick Start Guide - ANN Library

## Using the Library in Your Project

### Option 1: Direct Compilation

Add these files to your project and compile:

**Public Headers (include in your code):**
```cpp
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingSet.h"
#include "ann/TrainingConfig.h"
```

**Compile command:**
```bash
g++ -std=c++17 -I/path/to/ann/include -I/path/to/ann/src \
    your_code.cpp \
    /path/to/ann/src/ArtificialNeuralNetwork.cpp \
    /path/to/ann/src/Layer.cpp \
    /path/to/ann/src/Neuron.cpp \
    /path/to/ann/src/Connection.cpp \
    /path/to/ann/src/TrainingSet.cpp \
    -o your_program
```

### Option 2: Using CMake

Add to your `CMakeLists.txt`:

```cmake
# Add ANN library
add_subdirectory(path/to/artificial-neural-network)

# Link to your executable
add_executable(your_program your_code.cpp)
target_link_libraries(your_program PRIVATE ann)
```

### Option 3: Install System-Wide (Coming Soon)

```bash
cd artificial-neural-network/build
cmake ..
sudo make install
```

Then in your project:
```cmake
find_package(ANN REQUIRED)
target_link_libraries(your_program PRIVATE ann::ann)
```

## Simple Example

Create `my_network.cpp`:

```cpp
#include <iostream>
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingSet.h"
#include "ann/TrainingConfig.h"

int main() {
    using namespace ann;
    
    // 1. Create network
    std::vector<unsigned> topology = {2, 4, 1};  // 2 inputs, 4 hidden, 1 output
    ArtificialNeuralNetwork network(topology);
    
    // 2. Load data
    TrainingSet data;
    data.read("train.csv");
    
    // 3. Configure training
    TrainingConfig config;
    config.epochs = 1000;
    config.learningRate = 0.15;
    config.verbose = true;
    
    // 4. Train
    network.train(data, config);
    
    // 5. Predict
    auto pred = network.predict({0.0, 1.0});
    std::cout << "Class: " << pred.classLabel 
              << " Confidence: " << pred.confidence << std::endl;
    
    return 0;
}
```

Compile and run:
```bash
# From the ann directory
g++ -std=c++17 -I./include -I./src -o my_network \
    my_network.cpp \
    src/ArtificialNeuralNetwork.cpp \
    src/Layer.cpp src/Neuron.cpp \
    src/Connection.cpp src/TrainingSet.cpp

./my_network
```

## Example: Custom Training Callbacks

```cpp
#include "ann/ArtificialNeuralNetwork.h"
#include "ann/TrainingConfig.h"

int main() {
    using namespace ann;
    
    ArtificialNeuralNetwork network({2, 4, 1});
    TrainingSet data;
    data.read("train.csv");
    
    TrainingConfig config;
    config.epochs = 5000;
    config.verbose = false;  // Disable default output
    
    // Custom progress monitoring
    int bestEpoch = 0;
    double bestError = 1.0;
    
    config.progressCallback = [&](int epoch, double error) {
        if (error < bestError) {
            bestError = error;
            bestEpoch = epoch;
            std::cout << "New best: Epoch " << epoch 
                      << " - Error: " << error << std::endl;
        }
    };
    
    // Early stopping
    config.epochCallback = [](int epoch, double error) {
        // Stop if error is good enough
        return error > 0.001;  // Continue training while error > threshold
    };
    
    network.train(data, config);
    
    std::cout << "Training stopped. Best: Epoch " << bestEpoch 
              << " with error " << bestError << std::endl;
    
    return 0;
}
```

## Example: Batch Predictions

```cpp
#include "ann/ArtificialNeuralNetwork.h"

int main() {
    using namespace ann;
    
    ArtificialNeuralNetwork network({2, 4, 1});
    // ... train network ...
    
    // Prepare multiple inputs
    std::vector<std::vector<double>> testData = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };
    
    // Predict all at once
    auto predictions = network.predictBatch(testData);
    
    // Display results
    for (size_t i = 0; i < predictions.size(); ++i) {
        std::cout << "Input " << i << ": "
                  << "Class = " << predictions[i].classLabel 
                  << ", Confidence = " << predictions[i].confidence 
                  << std::endl;
    }
    
    return 0;
}
```

## Training Data Format

CSV file with features and class label:
```
feature1,feature2,...,featureN,classLabel
0.0,0.0,0
0.0,1.0,1
1.0,0.0,1
1.0,1.0,0
```

## Common Tasks

### Adjust Learning Parameters
```cpp
TrainingConfig config;
config.learningRate = 0.2;   // Higher = faster but less stable
config.momentum = 0.9;       // Higher = smoother convergence
config.epochs = 2000;        // More epochs = more training
```

### Monitor Training Progress
```cpp
config.verbose = true;        // Enable console output
config.printInterval = 100;   // Print every 100 epochs
```

### Access Training History
```cpp
network.train(data, config);
auto history = network.getTrainingHistory();

// Plot or analyze error over time
for (size_t i = 0; i < history.size(); ++i) {
    std::cout << "Epoch " << i << ": " << history[i] << std::endl;
}
```

### Scale Your Data
```cpp
TrainingSet data;
data.read("train.csv");
data.scale();  // Normalize to [0, 1] range
network.train(data, config);
```

## Tips

1. **Start with smaller learning rates** (0.1-0.2) for stability
2. **Use more epochs** if training error isn't decreasing
3. **Scale your data** for better performance
4. **Monitor training** with callbacks to detect issues
5. **Experiment with topology** - more hidden neurons for complex problems

## Troubleshooting

**Error: Input size mismatch**
- Check that your input vector size matches the first layer size in topology
- Remember: topology[0] should equal number of features

**Poor training performance**
- Try scaling your data with `data.scale()`
- Increase epochs or adjust learning rate
- Add more hidden neurons

**Training too slow**
- Increase learning rate (but watch for instability)
- Reduce number of epochs if error is already low
- Use smaller dataset for experimentation

## Full Example: XOR Problem

See `examples/xor_classification.cpp` for a complete working example that:
- Creates a network
- Loads training data
- Configures training with callbacks
- Trains the network
- Tests predictions before and after training
- Displays results with accuracy metrics
