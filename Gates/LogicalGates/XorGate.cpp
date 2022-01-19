#include "XorGate.hpp"

// CONSTRUCTORS
// private
XorGate::XorGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
XorGate::XorGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
XorGate::XorGate(const XorGate& clone) : XorGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
XorGate::XorGate(const XorGate* clone) : XorGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void XorGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("xor");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		(this->getGates().at(0)->getValue() && !this->getGates().at(1)->getValue())
		|| (!this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue())
	);
}

void XorGate::drawGate(Drawing& d) { this->draw(d, "XOR", 1); }