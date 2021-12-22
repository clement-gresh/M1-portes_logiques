#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const Gate* gate1, const Gate* gate2) : Gate{}, gate1{ gate1 }, gate2{ gate2 } {
}

// ACCESSORS
const Gate* LogicalGate::getGate1() const { return this->gate1; }
const Gate* LogicalGate::getGate2() const { return this->gate2; }