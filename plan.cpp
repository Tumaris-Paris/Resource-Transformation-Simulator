// AUTHOR:   Tumaris Paris
// FILENAME: plan.cpp
// DATE:     02/01/2024
// DESCRIPTION: Implements the Plan class.

#include "plan.h"
#include "formula.h"
#include <stdexcept>
#include <utility>

using namespace std;

// Constructor: Initializes a Plan object with an array of initial formulas and size.
Plan::Plan(Formula *initialFormulas, int initialSize) {
    size = initialSize;
    capacity = initialSize;
    formulas = new Formula[capacity];
    for (int i = 0; i < size; ++i) {
        formulas[i] = initialFormulas[i];
    }
}

// Copy Constructor: Creates a new Plan object by copying another Plan object.
Plan::Plan(const Plan &other) {
    size = other.size;
    capacity = other.capacity;
    formulas = new Formula[capacity];
    for (int i = 0; i < size; ++i) {
        formulas[i] = other.formulas[i];
    }
}

// Move Constructor: Creates a new Plan object by moving another Plan object.
Plan::Plan(Plan &&other) noexcept {
    formulas = other.formulas;
    size = other.size;
    capacity = other.capacity;

    other.formulas = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Copy Assignment Operator: Copies the content of another Plan object to this one.
Plan &Plan::operator=(const Plan &other) {
    if (this != &other) {
        Formula *newFormulas = new Formula[other.capacity];
        for (int i = 0; i < other.size; ++i) {
            newFormulas[i] = other.formulas[i];
        }
        delete[] formulas;
        formulas = newFormulas;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

// Move Assignment Operator: Moves the content of another Plan object to this one.
Plan &Plan::operator=(Plan &&other) noexcept {
    if (this != &other) {
        delete[] formulas;
        formulas = other.formulas;
        size = other.size;
        capacity = other.capacity;

        other.formulas = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Destructor: Destroys the Plan object and frees its resources.
Plan::~Plan() {
    delete[] formulas;
}

// Add: Adds a new formula at the end of the Plan.
void Plan::Add(Formula &&formula) {
    if (size == capacity) {
        ResizeIfNeeded();
    }
    formulas[size++] = std::move(formula);
}

// Remove: Removes the last formula from the Plan.
void Plan::Remove() {
    if (size > 0) {
        --size;
    }
}

// Replace: Replaces a formula at a specified index.
void Plan::Replace(int index, Formula &&formula) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    formulas[index] = std::move(formula);
}

// ResizeIfNeeded: Expands the capacity of the Plan when the current capacity is
// not enough to hold more formulas.
void Plan::ResizeIfNeeded() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Formula *newFormulas = new Formula[newCapacity];
    for (int i = 0; i < size; ++i) {
        newFormulas[i] = std::move(formulas[i]);
    }
    delete[] formulas;
    formulas = newFormulas;
    capacity = newCapacity;
}

// DisplayFormulas: Returns a string containing information about all formulas.
string Plan::DisplayFormulas() const {
    if (size == 0) {
        return "No formula";
    }
    string output;
    for (int i = 0; i < size; ++i) {
        output += "Formula " + to_string(i + 1) + ": " + formulas[i].Apply() +
                  "\n";
    }
    return output;
}

bool Plan::operator==(const Plan& other) const {
    if (size != other.size) {
        return false; // Different number of formulas
    }

    for (int i = 0; i < size; ++i) {
        if (!(formulas[i] == other.formulas[i])) {
            return false; // Found formulas that are not equal
        }
    }

    // All checks passed, plans are equal
    return true;
}

bool Plan::operator!=(const Plan& other) const {
    return !(*this == other);
}

bool Plan::operator>(const Plan& other) const {
    return this->size > other.size;
}

bool Plan::operator<(const Plan& other) const {
    return this->size < other.size;
}

bool Plan::operator<=(const Plan& other) const {
    return this->size <= other.size;
}


// =============================================================================
// ------------------------ IMPLEMENTATION INVARIANTS ---------------------------
// =============================================================================
// The implementation of the Plan class adheres to several invariants ensuring
// the correctness of its functionality:
//
// 1. Constructor:
//    - The constructor initializes a Plan object with an array of initial formulas
//      and size. It allocates dynamic memory for the formulas array, copying the
//      provided formulas.
//
// 2. Copy Constructor:
//    - The copy constructor creates a new Plan object by deep copying another Plan
//      object. It ensures that the new Plan has its own copy of the formulas.
//
// 3. Move Constructor:
//    - The move constructor transfers ownership of resources from another Plan
//      object to the new Plan object. It efficiently transfers the formulas array
//      and resets the other Plan's resources.
//
// 4. Copy Assignment Operator:
//    - The copy assignment operator replaces the content of one Plan object with
//      a deep copy of another Plan object. It ensures that the original memory
//      is deallocated and new memory is allocated for the copy.
//
// 5. Move Assignment Operator:
//    - The move assignment operator transfers ownership of resources from another
//      Plan object to the current Plan object. It efficiently transfers the
//      formulas array and resets the other Plan's resources.
//
// 6. Destructor:
//    - The destructor deallocates the memory used by the formulas array, ensuring
//      that there are no memory leaks.
//
// 7. Add:
//    - The Add method adds a new formula to the end of the Plan. It checks if the
//      current capacity is sufficient and resizes the array if necessary.
//
// 8. Remove:
//    - The Remove method removes the last formula from the Plan, effectively
//      reducing its size.
//
// 9. Replace:
//    - The Replace method replaces a formula at a specified index in the Plan. It
//      performs bounds checking to ensure the index is valid.
//
// 10. ResizeIfNeeded:
//     - The ResizeIfNeeded method expands the capacity of the Plan when the current
//       capacity is insufficient to hold more formulas. It dynamically adjusts the
//       capacity and transfers existing formulas to the new memory.
//
// 11. DisplayFormulas:
//     - The DisplayFormulas method generates a string containing information about
//       all the formulas in the Plan. It handles cases where there are no formulas
//       and formats the output with formula numbers and their respective results.
