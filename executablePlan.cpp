#include "executablePlan.h"
#include "stockpile.h"
#include <stdexcept>
#include <utility> // For std::move

// Constructor initializes the executable plan with initial formulas
ExecutablePlan::ExecutablePlan(Formula *initialFormulas, int initialSize)
        : Plan(initialFormulas, initialSize), _currentStep(0) {}

// Copy constructor
ExecutablePlan::ExecutablePlan(const ExecutablePlan &other)
        : Plan(other), _currentStep(other._currentStep) {}

// Move constructor
ExecutablePlan::ExecutablePlan(ExecutablePlan &&other) noexcept
        : Plan(std::move(other)), _currentStep(other._currentStep) {
    other._currentStep = 0; // Reset the moved-from object's step
}

// Copy assignment operator
ExecutablePlan &ExecutablePlan::operator=(const ExecutablePlan &other) {
    if (this != &other) {
        Plan::operator=(other); // Call base class copy assignment operator
        _currentStep = other._currentStep;
    }
    return *this;
}

// Move assignment operator
ExecutablePlan &ExecutablePlan::operator=(ExecutablePlan &&other) noexcept {
    if (this != &other) {
        Plan::operator=(std::move(other)); // Call base class move assignment operator
        _currentStep = other._currentStep;
        other._currentStep = 0; // Reset the moved-from object's step
    }
    return *this;
}

// Returns the current execution step
int ExecutablePlan::GetCurrentStep() const {
    return _currentStep;
}

// Applies the formula at the current step and advances to the next step
std::string ExecutablePlan::ApplyCurrentFormula() {
    if (_currentStep >= size) {
        throw std::runtime_error("No more formulas to apply.");
    }
    std::string result = formulas[_currentStep].Apply();
    _currentStep++; // Advance to the next step
    return result;
}

// Replaces a formula at a specified index, ensuring it hasn't been applied yet
void ExecutablePlan::Replace(int index, Formula &&formula) {
    if (index < _currentStep) {
        throw std::runtime_error("Cannot replace a formula that has already been applied.");
    }
    Plan::Replace(index, std::move(formula));
}

// Removes the last formula, ensuring it hasn't been completed yet
void ExecutablePlan::Remove() {
    if (_currentStep >= size) {
        throw std::runtime_error("Cannot remove the last formula if it has already been completed.");
    }
    Plan::Remove();
}

// Assuming Formula has methods like: bool checkResources(Stockpile&), and apply(Stockpile&)
std::shared_ptr<Stockpile> ExecutablePlan::Apply(std::shared_ptr<Stockpile> inputStockpile) {
    if (_currentStep >= size) {
        throw std::runtime_error("No more formulas to apply.");
    }

    // Check if all required resources for the current formula are available
    bool resourcesAvailable = true;
    Formula& currentFormula = formulas[_currentStep];
    for (int i = 0; i < currentFormula.GetInputSize(); ++i) {
        std::string resourceName = currentFormula.GetInputName(i);
        int requiredQuantity = currentFormula.GetInputQuantity(i);
        if (inputStockpile->GetQuantity(resourceName) < requiredQuantity) {
            resourcesAvailable = false;
            break; // Break early if any required resource is not available
        }
    }

    if (!resourcesAvailable) {
        // If resources are not sufficient, handle as needed (e.g., throw an error)
        throw std::runtime_error("Insufficient resources to apply formula.");
    }

    // Deduct the necessary resources from the stockpile
    for (int i = 0; i < currentFormula.GetInputSize(); ++i) {
        std::string resourceName = currentFormula.GetInputName(i);
        int requiredQuantity = currentFormula.GetInputQuantity(i);
        inputStockpile->ConsumeResource(resourceName, requiredQuantity);
    }

    inputStockpile->StoreFormulaResult(currentFormula.Apply());

    // Advance to the next step
    _currentStep++;

    // For this implementation, we simply return the modified input stockpile.
    // Depending on your requirements, you might create a new stockpile or modify this logic.
    return inputStockpile;
}

bool ExecutablePlan::operator==(const ExecutablePlan& other) const {
    // Assume Plan::operator== is implemented or manually compare Plan parts
    return Plan::operator==(other) && _currentStep == other._currentStep;
}

bool ExecutablePlan::operator!=(const ExecutablePlan& other) const {
    return !(*this == other);
}

bool ExecutablePlan::operator>(const ExecutablePlan& other) const {
    return _currentStep > other._currentStep;
}

bool ExecutablePlan::operator<(const ExecutablePlan& other) const {
    return _currentStep < other._currentStep;
}

bool ExecutablePlan::operator<=(const ExecutablePlan& other) const {
    return _currentStep < other._currentStep;
}

ExecutablePlan& ExecutablePlan::operator++() {
    // Assuming _currentStep increment is valid operation
    ++_currentStep;
    return *this;
}

