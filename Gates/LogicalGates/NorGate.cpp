#include "NorGate.hpp"

// CONSTRUCTORS
// private
NorGate::NorGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
NorGate::NorGate(Gate* const a, Gate* const b) : LogicalGate{ {a, b} } {}
NorGate::NorGate(const NorGate& clone) : NorGate{ clone.getGates().at(0), clone.getGates().at(1) } {}
NorGate::NorGate(const NorGate* clone) : NorGate{ clone->getGates().at(0), clone->getGates().at(1) } {}


// METHODS
void NorGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("nor");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		!(this->getGates().at(0)->getValue() || this->getGates().at(1)->getValue())
	);
}

void NorGate::drawGate(Drawing& d) { this->draw(d, "NOR", 1); }