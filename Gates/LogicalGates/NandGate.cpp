#include "NandGate.hpp"

// CONSTRUCTORS
// private
NandGate::NandGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
NandGate::NandGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
NandGate::NandGate(const NandGate& clone) : NandGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
NandGate::NandGate(const NandGate* clone) : NandGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void NandGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("nand");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		!(this->getGates().at(0)->getValue() && this->getGates().at(1)->getValue())
	);
}

void NandGate::drawGate(Drawing& d) { this->draw(d, "NAND", 1); }