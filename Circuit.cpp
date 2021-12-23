#include "Circuit.hpp"

// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates } {}


// METHODS
void Circuit::addLogicalGate(LogicalGate* const logicalGate) {
	this->logicalGates.push_back(logicalGate);
}

void Circuit::addCircuitGate(Gate* const gate){
	this->circuitGates.push_back(gate);
}

void Circuit::simulateCircuit() {
	// Reinitialization of the circuit
	this->circuitGates.clear();
	for (LogicalGate* logicalGate : this->getLogicalGates()) {
		logicalGate->setAlreadyUpdated(false);
	}

	// Adding the inputs to the circuit
	for (InputGate* gate : this->getInputGates()) {
		std::cout << "Value of Gate \"" << gate->getName() << "\" (true / false)" << std::endl;
		bool newValue;
		std::cin >> newValue;
		gate->setValue(newValue);
		this->addCircuitGate(gate);
	}

	bool circuitCompleted = false;

	while (!circuitCompleted) {
		circuitCompleted = true;

		// Adding to the circuit the logical gates for which the inputs are ready (i.e. intpus are either InputGate or updated LogicalGate)
		for (LogicalGate* logicalGate : this->getLogicalGates()) {
			if (!logicalGate->getAlreadyUpdated()) {
				bool canBeUpdated = true;

				for (Gate* input : logicalGate->getGates()) {
					if (std::find(this->getCircuitGates().begin(), this->getCircuitGates().end(), input) == this->getCircuitGates().end()) {
						canBeUpdated = false;
						circuitCompleted = false;
					}
				}

				if (canBeUpdated) {
					logicalGate->updateValue();
					logicalGate->setAlreadyUpdated(true);
					this->addCircuitGate(logicalGate);

					std::cout << "Value of Gate \"" << logicalGate->getType() << "\" : " << logicalGate->getValue();
					std::cout << ". Press enter to update the next gate." << std::endl;

					std::string anyKey;
					std::cin >> anyKey;
				}
			}
		}
	}


	/*
	for (LogicalGate* logicalGate : this->getLogicalGates()) {
		for (Gate* input : logicalGate->getGates()) {
			if(input->getType() == GateType::INPUT) {}
		}
	}
	*/

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

const std::vector<Gate*>& Circuit::getCircuitGates() const { return this->circuitGates; }
