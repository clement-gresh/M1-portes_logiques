#include "AndGate.hpp"

// CONSTRUCTORS
// private
AndGate::AndGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
AndGate::AndGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
AndGate::AndGate(const AndGate& clone) : AndGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
AndGate::AndGate(const AndGate* clone) : AndGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void AndGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("and");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue()
	);
}

void AndGate::drawGate(Drawing& d) { this->draw(d, "AND", 1); }