#include "Circuit.hpp"

// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates } {}


// METHODS
void Circuit::addLogicalGate(LogicalGate* const logicalGate) {
	this->logicalGates.push_back(logicalGate);
}

/*
void Circuit::addCircuitGate(Gate* const gate){
	this->circuitGates.push_back(gate);
}
*/

void Circuit::simulateCircuit() {
	// Reinitializing of the circuit
	for (LogicalGate* logicalGate : this->getLogicalGates()) {
		logicalGate->setAlreadyUpdated(false);
	}

	// Assigning a value to each input
	for (InputGate* gate : this->getInputGates()) {
		std::cout << "Please enter the value of Gate \"" << gate->getName() << "\" (0 / 1)" << std::endl;

		bool newValue;
		std::cin >> newValue;
		std::cout << std::endl;
		gate->setValue(newValue);
	}

	bool circuitCompleted = false;

	while (!circuitCompleted) {
		circuitCompleted = true;

		// Adding to the circuit the logical gates for which the inputs are ready (i.e. intpus are either InputGate or updated LogicalGate)
		for (LogicalGate* logicalGate : this->getLogicalGates()) {
			if (!logicalGate->getAlreadyUpdated()) {
				bool canBeUpdated = true;

				for (Gate* input : logicalGate->getGates()) {
					if (!input->getAlreadyUpdated()) {
						canBeUpdated = false;
						circuitCompleted = false;
					}
				}

				if (canBeUpdated) {
					logicalGate->updateValue();
					logicalGate->setAlreadyUpdated(true);

					std::cout << "Value of Gate \"" << logicalGate->getType() << "\" : " << logicalGate->getValue();
					std::cout << ". Press any key then enter to update the next gate.";

					std::string anyKey;
					std::cin >> anyKey;
					std::cout << std::endl;
				}
			}
		}
	}

	for (OutputGate* gate : this->getOutputGates()) {
		gate->updateValue();
		std::cout << "The value of the Output Gate \"" << gate->getName() << "\"  is : " << gate->getValue() << std::endl;
	}

	/* // debug : option 1
	for (OutputGate* outputGate : this->getOutputGates()) {

		LogicalGate* logicalGate = outputGate->getLogicalGate();
		
		nextGate(logicalGate);

		this->circuitGates.push_back(outputGate);
	}
	*/
}

/* // debug : option 1
With a fex modifications, this method could allow to only enter the OutputGates in the circuit 
(then the Input and Logical Gates can be fetched automatically)

void Circuit::nextGate(LogicalGate* const logicalGate) {
	this->circuitGates.push_back(logicalGate);

	for (Gate* next : logicalGate->getGates()) {

		if (next->getType() != GateType::INPUT) {
			nextGate((LogicalGate * ) next);
		}

		this->circuitGates.push_back(next);
	}
}
*/

// ACCESSORS
const std::vector<InputGate*>& Circuit::getInputGates() const { return this->inputGates; }

const std::vector<LogicalGate*>& Circuit::getLogicalGates() const { return this->logicalGates; }

const std::vector<OutputGate*>& Circuit::getOutputGates() const { return this->outputGates; }

//const std::vector<Gate*>& Circuit::getCircuitGates() const { return this->circuitGates; }
