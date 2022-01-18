#include "NxorGate.hpp"

// CONSTRUCTORS
// private
NxorGate::NxorGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
NxorGate::NxorGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
NxorGate::NxorGate(const NxorGate& clone) : NxorGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
NxorGate::NxorGate(const NxorGate* clone) : NxorGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void NxorGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("nxor");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		(!this->getGates().at(0)->getValue() && !this->getGates().at(1)->getValue())
		|| (this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue())
	);
}

void NxorGate::drawGate(Drawing& d) { this->draw(d, "NXOR", 1); }