#include "stockpile.h"
#include <iostream>

Stockpile::Stockpile() = default;

void Stockpile::AddResource(const std::string& name, int quantity) {
    resources[name] += quantity;
}

bool Stockpile::ConsumeResource(const std::string& name, int quantity) {
    if (resources.find(name) != resources.end() && resources[name] >= quantity) {
        resources[name] -= quantity;
        return true;
    }
    return false;
}

int Stockpile::GetQuantity(const std::string& name) const {
    auto it = resources.find(name);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

void Stockpile::StoreFormulaResult(const std::string& result) {
    applyResults.push_back(result);
}

std::vector<std::string>& Stockpile::GetApplyResults() {
    return applyResults;
};
