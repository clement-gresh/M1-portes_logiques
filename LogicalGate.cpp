#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates }, alreadyUpdated{ false } {}


// ACCESSORS
const std::vector<Gate*> LogicalGate::getGates() const { return this->gates; }

const bool LogicalGate::getAlreadyUpdated() const { return this->alreadyUpdated; }

void LogicalGate::setAlreadyUpdated(const bool alreadyUpdated) { this->alreadyUpdated = alreadyUpdated; }



/*
// CONSTRUCTORS
LogicalGate::LogicalGate(const Gate* gate1, const Gate* gate2) : Gate{}, gate1{ gate1 }, gate2{ gate2 } {}

// ACCESSORS
const Gate* LogicalGate::getGate1() const { return this->gate1; }
const Gate* LogicalGate::getGate2() const { return this->gate2; }
*/
