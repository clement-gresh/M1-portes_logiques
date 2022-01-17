#include "AndGate.hpp"

// CONSTRUCTORS
AndGate::AndGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}


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


void AndGate::drawGate(Drawing& d) {
	d.draw(this->gateLine, this->gateColumn - 1, "A");
	d.draw(this->gateLine, this->gateColumn, "N");
	d.draw(this->gateLine, this->gateColumn + 1, "D");
	d.draw(this->gateLine, this->gateColumn + 2, ":");
	std::string val = this->value ? "1" : "0";
	d.draw(this->gateLine, this->gateColumn + 3, val);
}