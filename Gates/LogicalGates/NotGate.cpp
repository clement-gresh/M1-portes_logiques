#include "NotGate.hpp"


// CONSTRUCTORS
// private
NotGate::NotGate() : LogicalGate{ std::vector<Gate*>{} } {}

//public
NotGate::NotGate(Gate* const a) : LogicalGate{ {a} } {}
NotGate::NotGate(const NotGate& clone) : NotGate{ clone.getGates().at(0) } {}
NotGate::NotGate(const NotGate* clone) : NotGate{ clone->getGates().at(0) } {}


// METHODS
void NotGate::updateGate() {
	// Updating the logical function corresponding to this gate
	std::string function = this->logicalFunction("not");
	this->setLogicalFunction(function);

	// Updating the value of the gate
	this->setValue(
		!this->getGates().at(0)->getValue() 
	);
}

void NotGate::drawGate(Drawing& d) { this->draw(d, "NOT", 1); }