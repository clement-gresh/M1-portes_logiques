#include "AndGate.hpp"

// CONSTRUCTORS
AndGate::AndGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}


// METHODS
void AndGate::updateGate() {
	LogicalGate::updateGate();

	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("and");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue()
	);
}

std::string const AndGate::getName(){ return "AND"; }
