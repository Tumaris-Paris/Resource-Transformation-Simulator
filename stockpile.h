#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <map>
#include <string>
#include <vector>


class Stockpile {
public:
    Stockpile();
    Stockpile(const Stockpile&) = delete; // Suppress copying
    Stockpile& operator=(const Stockpile&) = delete;

    void AddResource(const std::string& name, int quantity);
    bool ConsumeResource(const std::string& name, int quantity);
    int GetQuantity(const std::string& name) const;

    // New method to store formula application results
    void StoreFormulaResult(const std::string& result);

    // New method to display stored formula results
    std::vector<std::string>& GetApplyResults();

private:
    std::map<std::string, int> resources;
    std::vector<std::string> applyResults; // Stores results of formula applications
};

#endif // STOCKPILE_H
