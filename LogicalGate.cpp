#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates } {}


// ACCESSORS
const std::vector<Gate*> LogicalGate::getGates() const { return this->gates; }
