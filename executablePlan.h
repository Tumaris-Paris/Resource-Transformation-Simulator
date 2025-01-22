#ifndef EXECUTABLEPLAN_H
#define EXECUTABLEPLAN_H

#include "stockpile.h"
#include "Plan.h"

class ExecutablePlan : public Plan {
private:
    int _currentStep; // Tracks the current execution step of the plan

public:
    // Constructor that initializes the plan with an array of formulas and size
    ExecutablePlan(Formula* initialFormulas, int initialSize);

    // Copy constructor
    ExecutablePlan(const ExecutablePlan& other);

    // Move constructor
    ExecutablePlan(ExecutablePlan&& other) noexcept;

    // Copy assignment operator
    ExecutablePlan& operator=(const ExecutablePlan& other);

    // Move assignment operator
    ExecutablePlan& operator=(ExecutablePlan&& other) noexcept;

    // Returns the current execution step
    int GetCurrentStep() const;

    // Applies the formula at the current step and advances to the next step
    std::string ApplyCurrentFormula();

    // Overrides Plan's Replace method to include validation
    void Replace(int index, Formula&& formula) ;

    // Overrides Plan's Remove method to include validation
    void Remove() ;

    std::shared_ptr<Stockpile> Apply(std::shared_ptr<Stockpile> stockpile);

    bool operator==(const ExecutablePlan& other) const;
    bool operator!=(const ExecutablePlan& other) const;
    bool operator>(const ExecutablePlan& other) const;
    bool operator<(const ExecutablePlan& other) const;
    bool operator<=(const ExecutablePlan& other) const;
    ExecutablePlan& operator++();
};

#endif // EXECUTABLEPLAN_H
