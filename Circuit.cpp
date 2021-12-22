#include "Circuit.hpp"

// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates } {}


// METHODS
void Circuit::addLogicalGate(LogicalGate* logicalGate) {
	this->logicalGates.push_back(logicalGate);
}

void Circuit::simulateCircuit() {
	for (OutputGate* ogate : this->getOutputGates()) {
		break; //debug
	}
}


// ACCESSORS
const std::vector<InputGate*>& Circuit::getInputGates() const { return this->inputGates; }

const std::vector<LogicalGate*>& Circuit::getLogicalGates() const { return this->logicalGates; }

const std::vector<OutputGate*>& Circuit::getOutputGates() const { return this->outputGates; }