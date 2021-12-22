#include "AndGate.hpp"

// CONSTRUCTORS
AndGate::AndGate(const Gate* a, const Gate* b) : LogicalGate{a, b} {}


// METHODS
void AndGate::updateValue() {
	this->setValue(
		this->getGate1()->getValue() && this->getGate2()->getValue()
	);
}