// AUTHOR:   Tumaris Paris
// FILENAME: formula.cpp
// DATE:     02/01/2024
// DESCRIPTION: Implements the Formula class.

#include <iostream>
#include "formula.h"

using namespace std;

// Default constructor
Formula::Formula() {
    inputNames = nullptr;
    inputQuantities = nullptr;
    outputNames = nullptr;
    outputQuantities = nullptr;
    inputSize = 0;
    outputSize = 0;
    proficiencyLevel = 0;
}

// Parameterized constructor for initializing formula components
Formula::Formula(
        string *inputNames, int *inputQuantities, int inputSize,
        string *outputNames, int *outputQuantities, int outputSize
) {
    for (int i = 0; i < inputSize; ++i) {
        if (inputQuantities[i] < 0) {
            throw invalid_argument("Negative value found in inputQuantities");
        }
    }
    for (int i = 0; i < outputSize; ++i) {
        if (outputQuantities[i] < 0) {
            throw invalid_argument("Negative value found in outputQuantities");
        }
    }
    this->inputNames = inputNames;
    this->inputQuantities = inputQuantities;
    this->inputSize = inputSize;
    this->outputNames = outputNames;
    this->outputQuantities = outputQuantities;
    this->outputSize = outputSize;
    proficiencyLevel = 0;
}

// Copy constructor
Formula::Formula(const Formula &other) {
    inputSize = other.inputSize;
    outputSize = other.outputSize;
    proficiencyLevel = other.proficiencyLevel;

    inputNames = new string[inputSize];
    inputQuantities = new int[inputSize];
    for (int i = 0; i < inputSize; ++i) {
        inputNames[i] = other.inputNames[i];
        inputQuantities[i] = other.inputQuantities[i];
    }

    outputNames = new string[outputSize];
    outputQuantities = new int[outputSize];
    for (int i = 0; i < outputSize; ++i) {
        outputNames[i] = other.outputNames[i];
        outputQuantities[i] = other.outputQuantities[i];
    }
}

// Copy assignment operator
Formula &Formula::operator=(const Formula &other) {
    if (this != &other) {
        delete[] inputNames;
        delete[] inputQuantities;
        delete[] outputNames;
        delete[] outputQuantities;

        inputSize = other.inputSize;
        outputSize = other.outputSize;
        proficiencyLevel = other.proficiencyLevel;

        inputNames = new string[inputSize];
        inputQuantities = new int[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            inputNames[i] = other.inputNames[i];
            inputQuantities[i] = other.inputQuantities[i];
        }

        outputNames = new string[outputSize];
        outputQuantities = new int[outputSize];
        for (int i = 0; i < outputSize; ++i) {
            outputNames[i] = other.outputNames[i];
            outputQuantities[i] = other.outputQuantities[i];
        }
    }
    return *this;
}

// Move constructor
Formula::Formula(Formula &&other) noexcept {
    inputNames = other.inputNames;
    inputQuantities = other.inputQuantities;
    inputSize = other.inputSize;
    outputNames = other.outputNames;
    outputQuantities = other.outputQuantities;
    outputSize = other.outputSize;
    proficiencyLevel = other.proficiencyLevel;
    gen = other.gen;
    dis = other.dis;

    other.inputNames = nullptr;
    other.inputQuantities = nullptr;
    other.outputNames = nullptr;
    other.outputQuantities = nullptr;
}

// Move assignment operator
Formula &Formula::operator=(Formula &&other) noexcept {
    if (this != &other) {
        delete[] inputNames;
        delete[] inputQuantities;
        delete[] outputNames;
        delete[] outputQuantities;

        inputNames = other.inputNames;
        inputQuantities = other.inputQuantities;
        inputSize = other.inputSize;
        outputNames = other.outputNames;
        outputQuantities = other.outputQuantities;
        outputSize = other.outputSize;
        proficiencyLevel = other.proficiencyLevel;
        gen = other.gen;
        dis = other.dis;

        other.inputNames = nullptr;
        other.inputQuantities = nullptr;
        other.outputNames = nullptr;
        other.outputQuantities = nullptr;
    }
    return *this;
}

// Destructor
Formula::~Formula() {
    delete[] inputNames;
    delete[] inputQuantities;
    delete[] outputNames;
    delete[] outputQuantities;
}

const string Formula::GetInputName(int i) const {
    if (i >= 0 && i < inputSize) {
        return inputNames[i];
    }
    return ""; // Return empty string for invalid index
}

int Formula::GetInputQuantity(int i) const {
    if (i >= 0 && i < inputSize) {
        return inputQuantities[i];
    }
    return 0; // Return 0 for invalid index
}

int Formula::GetInputSize() const {
    return inputSize;
}

// Retrieves output component information by index
string Formula::GetOutput(int index) const {
    if (index < 0 || index >= outputSize) {
        throw out_of_range("Index out of range");
    }
    return outputNames[index] + ": " + to_string(outputQuantities[index]);
}

// Applies the formula and calculates output based on input and proficiency level
string Formula::Apply() {
    string result;
    double multiplier = DetermineMultiplier();

    for (int i = 0; i < outputSize; ++i) {
        int adjustedQuantity = static_cast<int>(outputQuantities[i] *
                                                multiplier);
        result += to_string(adjustedQuantity) + " " + outputNames[i];
        if (i < outputSize - 1) {
            result += ", ";
        }
    }

    return result;
}

// Determines the multiplier based on proficiency level and random chance
double Formula::DetermineMultiplier() {
    // Calculate the rates based on proficiency level
    int failureRate = static_cast<int>(InitialFailureRate * 100 -
                                       ProficiencyImpact * proficiencyLevel *
                                       100);
    int partialRate = static_cast<int>(InitialPartialOutputRate * 100 -
                                       ProficiencyImpact * proficiencyLevel *
                                       100);
    int normalRate = static_cast<int>(InitialNormalOutputRate * 100 +
                                      ProficiencyImpact * proficiencyLevel *
                                      100);

    // Determine output multiplier based on random chance
    int chance = dis(gen);
    if (chance < failureRate)
        return ZeroOutputMultiplier;
    else if (chance < failureRate + partialRate)
        return ReducedOutputMultiplier;
    else if (chance < failureRate + partialRate + normalRate)
        return StandardOutputMultiplier;
    else
        return EnhancedOutputMultiplier;
}

bool Formula::operator==(const Formula &other) const {
    if (inputSize != other.inputSize || outputSize != other.outputSize ||
        proficiencyLevel != other.proficiencyLevel) {
        return false;
    }

    for (int i = 0; i < inputSize; ++i) {
        if (inputNames[i] != other.inputNames[i] ||
            inputQuantities[i] != other.inputQuantities[i]) {
            return false;
        }
    }

    for (int i = 0; i < outputSize; ++i) {
        if (outputNames[i] != other.outputNames[i] ||
            outputQuantities[i] != other.outputQuantities[i]) {
            return false;
        }
    }

    // If all checks pass, the formulas are considered equal.
    return true;
}

bool Formula::operator!=(const Formula &other) const {
    return !(*this == other);
}

// =============================================================================
// ------------------------ IMPLEMENTATION INVARIANTS ---------------------------
// =============================================================================
// The Formula class's implementation adheres to the following invariants:
//
// 1. Internal Data Structures and Dependencies:
//    - The class utilizes dictionaries (_inputResources and _outputResources) to
//      manage resources efficiently.
//    - Proficiency level and rates (_failureRate, _partialRate, _normalRate) are
//      interdependent, ensuring consistency in output calculations.
//    - A Random object (_random) introduces variability in output calculation.
//
// 2. Error Response:
//    - Exception handling is employed:
//      - ArgumentNullException is thrown if input or output dictionaries are null
//        during construction.
//      - KeyNotFoundException is used if an attempt is made to access a
//        non-existent key in the resource dictionaries.
//      - ArgumentException or InvalidOperationException handles invalid proficiency
//        level increase attempts.
//
// 3. Output Calculation:
//    - The Apply() method dynamically calculates output based on the current state
//      and multipliers.
//    - Multipliers (ZeroOutputMultiplier, ReducedOutputMultiplier,
//      StandardOutputMultiplier, EnhancedOutputMultiplier) represent different
//      output scenarios.
//    - Output calculation involves randomness and rate-based decision logic.
//
// 4. Rate Adjustment Logic:
//    - Rates are recalculated in CalculateRates() when the proficiency level
//      changes, ensuring alignment with the current proficiency level.
