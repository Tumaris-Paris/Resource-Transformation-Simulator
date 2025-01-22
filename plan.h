// AUTHOR: Tumaris Paris
// FILENAME: plan.h
// DATE: 02/01/2024
// DESCRIPTION: The Plan class encapsulates a collection of Formula objects.
// It supports operations such as addition, removal, and replacement of formulas,
// alongside the ability to display the current set of formulas.

// =============================================================================
// ----------------------------- CLASS INVARIANTS ------------------------------
// =============================================================================
// The Plan class encapsulates a dynamic collection of Formula objects, providing
// functionalities to add, remove, and replace formulas within the collection. It
// maintains an internal array to store these formulas, dynamically resizing as
// necessary to accommodate changes in the collection size.
//
// INVARIANTS:
// - The Plan maintains an ordered collection of Formula objects, with operations
//   to modify this collection (addition, removal, replacement).
// - The internal storage scales dynamically with the collection size, ensuring
//   efficient use of memory.
// - Deep copy semantics ensure that copies of a Plan are entirely independent,
//   with no shared Formulas between them.
// - Move semantics provide efficient transfers of resources, particularly useful
//   for temporary Plans or when reassigning Plans.
// - Proper resource management is maintained throughout the Plan's lifecycle,
//   preventing memory leaks and ensuring consistent state integrity.

#ifndef P2_PLAN_H
#define P2_PLAN_H

#include "formula.h"
#include <string>

class Plan {
private:
    void ResizeIfNeeded();
    // Ensures capacity to add new Formulas, resizing array if necessary.
    // Preconditions: None.
    // Postconditions: Capacity increased if needed for additional Formulas.
protected:
    Formula* formulas; // Pointer to dynamically allocated array of Formulas.
    int size;          // Current number of Formulas in Plan.
    int capacity;      // Capacity of the formulas array.
public:
    Plan(Formula* initialFormulas, int initialSize);
    // Constructor initializes a Plan with an array of Formulas and their count.
    // Preconditions: initialFormulas points to a dynamically allocated array of
    //                Formulas, initialSize is non-negative.
    // Postconditions: The Plan is initialized with the specified Formulas.

    Plan(const Plan& other);
    // Copy constructor creates a deep copy of another Plan.
    // Preconditions: 'other' is a valid, existing Plan object.
    // Postconditions: A new Plan object is a deep copy of 'other'.

    Plan(Plan&& other) noexcept;
    // Move constructor transfers ownership of resources from another Plan.
    // Preconditions: 'other' is a valid Plan object about to be discarded.
    // Postconditions: The new Plan takes 'other's resources; 'other' is empty.

    Plan& operator=(const Plan& other);
    // Copy assignment operator replaces this Plan with a deep copy of another.
    // Preconditions: 'other' is a valid Plan object.
    // Postconditions: This Plan is a deep copy of 'other'.

    Plan& operator=(Plan&& other) noexcept;
    // Move assignment operator transfers resources from another Plan.
    // Preconditions: 'other' is a valid Plan object about to be discarded.
    // Postconditions: This Plan takes 'other's resources; 'other' is left empty.

    ~Plan();
    // Destructor cleans up dynamically allocated Formulas.
    // Preconditions: None.
    // Postconditions: Resources are freed.

    void Add(Formula &&formula);
    // Adds a new Formula to the Plan.
    // Preconditions: 'formula' is a valid Formula object.
    // Postconditions: 'formula' is added; size is incremented by 1.

    void Remove();
    // Removes the last Formula from the Plan.
    // Preconditions: Plan is not empty (size > 0).
    // Postconditions: Last Formula is removed; size is decremented by 1.

    void Replace(int index, Formula&& formula);
    // Replaces a Formula at a specific index with a new one.
    // Preconditions: 'index' within bounds (0 <= index < size), 'formula' valid.
    // Postconditions: Formula at 'index' is replaced with 'formula'.

    std::string DisplayFormulas() const;
    // Generates a string representation of all Formulas in the Plan.
    // Preconditions: None.
    // Postconditions: Returns string of Formulas, Plan's state unchanged.

    bool operator==(const Plan& other) const;
    bool operator!=(const Plan& other) const;
    bool operator>(const Plan& other) const;
    bool operator<(const Plan& other) const;
    bool operator<=(const Plan& other) const;
};

#endif
