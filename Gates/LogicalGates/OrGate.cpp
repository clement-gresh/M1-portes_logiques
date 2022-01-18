#include "OrGate.hpp"

// CONSTRUCTORS
// private
OrGate::OrGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
OrGate::OrGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
OrGate::OrGate(const OrGate& clone) : OrGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
OrGate::OrGate(const OrGate* clone) : OrGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void OrGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("or");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		this->getGates().at(0)->getValue() || this->getGates().at(1)->getValue()
	);
}

void OrGate::drawGate(Drawing& d) { this->draw(d, "OR_", 1); }