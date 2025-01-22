#include "executablePlan.h"
#include "formula.h"
#include "stockpile.h"
#include <iostream>
#include <memory>
#include <string>

// Function to create a Formula object using maps for input and output resources
Formula createFormula(
        const std::map<std::string, int> &inputResources,
        const std::map<std::string, int> &outputResources) {

    // Calculate sizes of input and output resources
    int inputSize = inputResources.size();
    int outputSize = outputResources.size();

    // Dynamically allocate arrays for names and quantities
    std::string *inputNames = new std::string[inputSize];
    int *inputQuantities = new int[inputSize];
    std::string *outputNames = new std::string[outputSize];
    int *outputQuantities = new int[outputSize];

    // Populate arrays from maps
    int i = 0;
    for (const auto &pair: inputResources) {
        inputNames[i] = pair.first;
        inputQuantities[i] = pair.second;
        ++i;
    }

    i = 0;
    for (const auto &pair: outputResources) {
        outputNames[i] = pair.first;
        outputQuantities[i] = pair.second;
        ++i;
    }

    // Create the Formula object
    Formula formula(inputNames, inputQuantities, inputSize, outputNames,
                    outputQuantities, outputSize);

    // Return the created Formula object
    return formula;
}

// Utility function to create a dynamic array of Formulas from a vector
Formula *createFormulasArray(
        const std::vector<std::pair<std::map<std::string, int>, std::map<std::string, int>>> &resources) {

    Formula *formulasArray = new Formula[resources.size()];
    for (size_t i = 0; i < resources.size(); ++i) {
        formulasArray[i] = createFormula(resources[i].first,
                                         resources[i].second);
    }
    return formulasArray;
}

// Test functions
void Test_Formula_Apply() {
    std::cout << "Testing Formula Application:\n";

    // Example input and output resources for a formula
    std::map<std::string, int> inputResources{{"Water", 2}, {"Carbon", 1}};
    std::map<std::string, int> outputResources{{"Glucose", 1}};

    // Create formula
    Formula formula = createFormula(inputResources, outputResources);

    // Simulate formula application
    std::string result = formula.Apply();
    std::cout << "Formula Application Result: " << result << std::endl;
}

void Test_Stockpile_AddResource() {
    std::cout << "\nTesting Stockpile Resource Addition:\n";

    // Create a stockpile
    Stockpile stockpile;

    // Add resources
    stockpile.AddResource("Water", 3);
    stockpile.AddResource("Carbon", 2);

    // Display added resources
    std::cout << "Water Quantity: " << stockpile.GetQuantity("Water") << std::endl;
    std::cout << "Carbon Quantity: " << stockpile.GetQuantity("Carbon") << std::endl;
}

void Test_ExecutablePlan_ApplyCurrentFormula() {
    std::cout << "\nTesting Executable Plan Formula Application:\n";

    // Prepare formulas for the executable plan
    std::vector<std::pair<std::map<std::string, int>, std::map<std::string, int>>> resources{
            {{{"Water", 2}, {"Carbon", 1}}, {{"Glucose", 1}}},
            {{{"Glucose", 1}, {"Sunlight", 1}}, {{"Oxygen", 2}, {"Energy", 1}}}
    };
    Formula* formulasArray = createFormulasArray(resources);
    int formulasCount = resources.size();

    // Create an executable plan with the formulas
    ExecutablePlan plan(formulasArray, formulasCount);

    // Create a stockpile with initial resources
    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>();
    stockpile->AddResource("Water", 2);
    stockpile->AddResource("Carbon", 2);
    stockpile->AddResource("Sunlight", 1);

    // Apply the first formula
    try {
        std::shared_ptr<Stockpile> updatedStockpile = plan.Apply(std::move(stockpile));
        for (const auto& result : updatedStockpile->GetApplyResults()) {
            std::cout << "Apply Result: " << result << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void Test_Formula_InsufficientResources() {
    std::cout << "\nTesting Formula Application with Insufficient Resources using createFormulasArray:\n";

    // Define resources for a formula that requires more resources than available
    std::vector<std::pair<std::map<std::string, int>, std::map<std::string, int>>> resources = {
            {{{"Water", 10}, {"Carbon", 5}}, {{"Oxygen", 4}}}
    };

    // Create formulas array
    Formula* formulasArray = createFormulasArray(resources);
    int formulasCount = resources.size();

    // Create an executable plan with the formula
    ExecutablePlan plan(formulasArray, formulasCount);

    // Create a stockpile with limited resources
    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>();
    stockpile->AddResource("Water", 2); // Not enough water
    stockpile->AddResource("Carbon", 5);

    // Attempt to apply the formula
    try {
        plan.Apply(stockpile);
    } catch (const std::exception& e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }

    // Clean up dynamically allocated resources
    delete[] formulasArray;
}

// Utility function to test replacing a formula in an executable plan
void Test_ExecutablePlan_ReplaceFormula() {
    std::cout << "\nTesting Replacing a Formula in Executable Plan using createFormulasArray:\n";

    // Initial formula resources
    std::vector<std::pair<std::map<std::string, int>, std::map<std::string, int>>> initialResources = {
            {{{"A", 1}}, {{"B", 2}}}
    };

    // Create initial formulas array
    Formula* initialFormulasArray = createFormulasArray(initialResources);
    int initialFormulasCount = initialResources.size();

    // Create an executable plan with the initial formula
    ExecutablePlan plan(initialFormulasArray, initialFormulasCount);

    // New formula resources
    std::vector<std::pair<std::map<std::string, int>, std::map<std::string, int>>> newResources = {
            {{{"C", 3}}, {{"D", 4}}}
    };

    // Create new formulas array for replacement
    Formula* newFormulasArray = createFormulasArray(newResources);

    // Replace the initial formula with the new formula
    plan.Replace(0, std::move(newFormulasArray[0]));

    // Verify the replacement by applying the plan
    std::shared_ptr<Stockpile> stockpile = std::make_shared<Stockpile>();
    stockpile->AddResource("C", 3);
    try {
        plan.Apply(stockpile);
        std::cout << "New formula applied successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // Clean up dynamically allocated resources
    delete[] initialFormulasArray;
    delete[] newFormulasArray;
}

int main() {
    Test_Formula_Apply();
    Test_Stockpile_AddResource();
    Test_ExecutablePlan_ApplyCurrentFormula();
    Test_Formula_InsufficientResources();
    Test_ExecutablePlan_ReplaceFormula();
    return 0;
}

