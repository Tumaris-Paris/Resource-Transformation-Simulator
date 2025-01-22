# Resource Transformation Simulator

## Overview

The **Resource Transformation Simulator** is a system designed to simulate resource transformation processes using formulas and plans. It allows for the management of resources in a stockpile, applying defined formulas to transform inputs into outputs in a sequence defined by a plan.

This project is versatile and can be adapted for various use cases such as manufacturing pipelines, crafting systems in games, chemical reaction simulations, or supply chain optimization.

---

## Features

- **Formula Execution**: Define and apply transformations of input resources into output resources.
- **Plan Management**: Execute a series of transformations in a logical order.
- **Stockpile Tracking**: Manage available resources and ensure sufficient quantities for transformations.
- **Error Handling**: Prevent transformations when resources are insufficient.
- **Customizable**: Easily extendable for various domains beyond chemistry.

---

## File Structure

```
ResourceTransformationSimulator/
├── CMakeLists.txt                  # Build configuration file
├── src/                            # Source code files
│   ├── simulator.cpp               # Main entry point
│   ├── formula.cpp                 # Handles resource formulas
│   ├── plan.cpp                    # Manages transformation plans
│   ├── executionPlan.cpp           # Executes transformation plans
│   ├── stockpile.cpp               # Manages resource storage
├── include/                        # Header files
│   ├── formula.h                   # Header for resource formulas
│   ├── plan.h                      # Header for transformation plans
│   ├── executionPlan.h             # Header for executable plans
│   ├── stockpile.h                 # Header for resource management
├── build/                          # Build output directory
├── README.md                       # Project documentation
```

---

## How to Build and Run

### Prerequisites

- A C++17 compatible compiler (e.g., GCC, Clang, MSVC).
- [CMake](https://cmake.org/) version 3.26 or later.

### Build Steps

1. Clone the project and navigate to its directory:
   ```bash
   cd /path/to/ResourceTransformationSimulator
   ```

2. Create and navigate to the build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure the project using CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

### Run the Program

After building, run the program:
```bash
./simulator
```

---

## Examples

### Example 1: Applying a Single Formula

Input resources:
- Water: 2 units
- Carbon: 1 unit

Formula:
- Input: 2 units of Water + 1 unit of Carbon
- Output: 1 unit of Glucose

Output:
- Water: 0 units
- Carbon: 0 units
- Glucose: 1 unit

### Example 2: Executing a Plan

Initial resources:
- Water: 4 units
- Carbon: 2 units
- Sunlight: 1 unit

Plan:
1. **Step 1**: Water + Carbon → Glucose
2. **Step 2**: Glucose + Sunlight → Oxygen + Energy

Final Output:
- Water: 2 units
- Carbon: 0 units
- Sunlight: 0 units
- Glucose: 0 units
- Oxygen: 2 units
- Energy: 1 unit

---

## Contributing

Contributions are welcome! If you’d like to contribute, please fork the repository and submit a pull request.

---

## Contact

For questions or feedback, please contact Tumarisparis@gmail.com

