# Unit Tests for Artificial Neural Network

This directory contains a comprehensive test suite for the ANN project using **Catch2**, a modern, header-only C++ testing framework.

## Test Files

- `test_ann.cpp` - Main test suite with unit tests for all components
- `catch.hpp` - Catch2 testing framework (single header file)

## Running the Tests

### Compile and run:
```bash
cd ANN/tests
g++ -std=c++17 -o test_ann test_ann.cpp ../ArtificialNeuralNetwork.cpp ../Layer.cpp ../Neuron.cpp ../Connection.cpp ../TrainingSet.cpp
./test_ann
```

Or from the ANN directory:
```bash
cd ANN
g++ -std=c++17 -o tests/test_ann tests/test_ann.cpp ArtificialNeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp TrainingSet.cpp
./tests/test_ann
```

### Run specific tests by tag:
```bash
./test_ann "[Connection]"    # Run only Connection tests
./test_ann "[Neuron]"         # Run only Neuron tests
./test_ann "[ANN]"            # Run only ANN tests
```

### Verbose output:
```bash
./test_ann -s    # Show all assertions, even passing ones
```

## Test Coverage

The test suite includes **15 unit tests** covering:

### Connection Tests (2 tests)
- Connection initialization with random weights
- Multiple connections have different weights

### Neuron Tests (3 tests)
- Neuron creation without output connections (output layer)
- Neuron creation with output connections (hidden layer)
- Setting and getting neuron output values

### Layer Tests (3 tests)
- Layer creation with specified topology
- Output layer creation (no outgoing connections)
- Neuron count validation (includes bias neuron)

### Training Set Tests (2 tests)
- Training set initialization
- Reading CSV files and parsing data

### Artificial Neural Network Tests (5 tests)
- Network creation with simple topology (2-3-1)
- Network creation with complex topology (4-6-3-2)
- Getting results from output layer
- Multiple output neurons
- Integration with training set loading

## Test Framework

The tests use **Catch2**, a modern C++ testing framework with the following features:

- **Natural syntax**: `TEST_CASE` and `SECTION` for organizing tests
- **Rich assertions**: `REQUIRE`, `REQUIRE_FALSE`, `Approx()` for floating-point comparisons
- **Tags**: Filter tests by category like `[Connection]`, `[Neuron]`, `[ANN]`
- **Detailed output**: Shows exact values on failures
- **Header-only**: No external dependencies or complex build setup

## Expected Output

When all tests pass, you should see:
```
===============================================================================
All tests passed (25 assertions in 15 test cases)
```

If a test fails, Catch2 will show:
- The exact assertion that failed
- Expected vs actual values
- File name and line number

## Adding New Tests

To add a new test with Catch2:

1. Define a test case:
```cpp
TEST_CASE("Description of what you're testing", "[Tag]") {
    // Arrange
    Connection conn;
    
    // Act & Assert
    REQUIRE(conn.weight >= -1.0);
    REQUIRE(conn.weight <= 1.0);
}
```

2. Use SECTION for related variations:
```cpp
TEST_CASE("Neuron value operations", "[Neuron]") {
    Neuron neuron(0, 0);
    
    SECTION("positive value") {
        neuron.setOutputValue(0.5);
        REQUIRE(neuron.getOutputValue() == 0.5);
    }
    
    SECTION("negative value") {
        neuron.setOutputValue(-0.5);
        REQUIRE(neuron.getOutputValue() == -0.5);
    }
}
```

3. Recompile and run the test suite

## Why Catch2?

- **Header-only**: Just one file (`catch.hpp`), no build complexity
- **Modern C++**: Clean syntax that reads like documentation
- **Professional**: Industry-standard framework used by many projects
- **Flexible**: Easy filtering by tags, verbose modes, custom output formats
