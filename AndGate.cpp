#include "AndGate.hpp"

// CONSTRUCTORS
AndGate::AndGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}


// METHODS
void AndGate::updateValue() {
	this->setValue(
		this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue()
	);
}