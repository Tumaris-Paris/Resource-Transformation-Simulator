// AUTHOR:   Tumaris Paris
// FILENAME: formula.h
// DATE:     02/01/2024
// DESCRIPTION: Defines the Formula class for managing chemical formulas.
//              This class supports deep copying and moving of Formula objects,
//              allowing for dynamic management of input and output chemical
//              components.

// =============================================================================
// ----------------------------- CLASS INVARIANTS ------------------------------
// =============================================================================
// The Formula class models a system with varying proficiency levels and
// output rates.
//
// 1. ProficiencyLevel is always in the range [0, MaxProficiency].
// 2. _failureRate, _partialRate, and _normalRate are non-negative and
//    dependent on ProficiencyLevel.
// 3. The sum of _failureRate, _partialRate, _normalRate, and the chance for
//    EnhancedOutputMultiplier does not exceed 100.
// 4. _inputResources and _outputResources are never null and do not contain
//    null keys.
// 5. The EnhancedOutputMultiplier is a constant factor representing an
//    enhanced output scenario.

#ifndef FORMULA_H
#define FORMULA_H

#include <stdexcept>
#include <string>
#include <random>
#include <cmath>

using namespace std;

class Formula {
public:
    Formula();
    // Default constructor.
    // Preconditions: None.
    // Postconditions: An empty Formula object is created with no inputs or outputs.


    Formula(std::string *inputNames, int *inputQuantities, int inputSize,
            std::string *outputNames, int *outputQuantities, int outputSize);
    // Parameterized constructor.
    // Preconditions: inputNames, inputQuantities, outputNames, and outputQuantities
    //                are non-null pointers to arrays of strings and ints, respectively.
    // Postconditions: A Formula object is created with the specified inputs and
    // outputs.

    Formula(const Formula &other);
    // Copy constructor.
    // Preconditions: 'other' is a valid, existing Formula object.
    // Postconditions: A new Formula object is created as a deep copy of 'other'.

    Formula &operator=(const Formula &other);
    // Copy assignment operator.
    // Preconditions: 'other' is a valid, existing Formula object.
    // Postconditions: This Formula is a deep copy of 'other'.

    Formula(Formula &&other) noexcept;
    // Move constructor.
    // Preconditions: 'other' is a valid, existing Formula object.
    // Postconditions: 'other' is left in an unspecified but valid state.

    Formula &operator=(Formula &&other) noexcept;
    // Move assignment operator.
    // Preconditions: 'other' is a valid, existing Formula object.
    // Postconditions: 'other' is left in an unspecified but valid state.

    ~Formula();
    // Destructor.
    // Preconditions: None.
    // Postconditions: Dynamically allocated resources are freed.

    bool operator==(const Formula& other) const;
    bool operator!=(const Formula& other) const;

    // Accessor methods for resources
    const string GetInputName(int i) const;
    int GetInputQuantity(int i) const;

    // Method to get the count of input resources
    int GetInputSize() const;

    string GetOutput(int index) const;
    // Returns the name of the output at the specified index.
    // Preconditions: 'index' is within the range of output array size.
    // Postconditions: Returns the output name without modifying the Formula object.

    string Apply();
    // Simulates the application of the formula.
    // Preconditions: None.
    // Postconditions: Returns a string indicating the success or failure of the
    // application.

private:
    std::string *inputNames; // Dynamically allocated array of input names
    int *inputQuantities;    // Dynamically allocated array of input quantities
    int inputSize;           // Size of the input arrays



    std::string *outputNames;    // Dynamically allocated array of output names
    int *outputQuantities;       // Dynamically allocated array of output quantities
    int outputSize;              // Size of the output arrays

    std::random_device rd;       // Random device for generating random numbers
    // Mersenne Twister generator
    std::mt19937 gen = std::mt19937(rd());
    // Uniform distribution for random numbers
    std::uniform_int_distribution<> dis =
            std::uniform_int_distribution<>(0, 100);

    int proficiencyLevel;        // Proficiency level affecting the formula outcome

    // Constants related to formula application outcomes
    const int MaxProficiency = 6;
    const double InitialFailureRate = 0.30;
    const double InitialPartialOutputRate = 0.25;
    const double InitialNormalOutputRate = 0.45;
    const double ProficiencyImpact = 0.05;

    const double ZeroOutputMultiplier = 0.0;
    const double ReducedOutputMultiplier = 0.75;
    const double StandardOutputMultiplier = 1.0;
    const double EnhancedOutputMultiplier = 1.10;

    double DetermineMultiplier();
    // Determines the output multiplier based on the proficiency level.
    // Preconditions: None.
    // Postconditions: Returns a multiplier value based on the proficiency level
    //                 which affects the formula's output efficiency.
};

#endif
