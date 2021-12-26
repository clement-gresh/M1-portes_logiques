#include "AndGate.hpp"

// CONSTRUCTORS
AndGate::AndGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {
	this->type = GateType::AND;
}


// METHODS
void AndGate::updateGate() {
	LogicalGate::updateGate();

	this->setValue(
		this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue()
	);
}