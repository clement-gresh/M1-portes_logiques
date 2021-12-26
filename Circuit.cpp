#include "Circuit.hpp"

// INITIALIZATION of constant static members
const int Circuit::LEVEL_HEIGHT{ 5 };
const int Circuit::GATE_WIDTH{ 5 };


// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates },
	  circuitDrawing{ std::vector<std::vector<std::string>>() } {}


// METHODS
void Circuit::addLogicalGate(LogicalGate* const logicalGate) {
	this->logicalGates.push_back(logicalGate);
}

void Circuit::simulateCircuit() {
	// Reinitializing the circuit
	for (LogicalGate* logicalGate : this->getLogicalGates()) {
		logicalGate->setAlreadyUpdated(false);
	}

	// Assigning a value to each input and adding them to the drawing
	int i = 0;
	for (InputGate* inputGate : this->getInputGates()) {
		inputGate->setGateLevel(i);
		std::cout << "Please enter the value of Gate \"" << inputGate->getName() << "\" (0 / 1)" << std::endl;

		bool newValue;
		std::cin >> newValue;
		std::cout << std::endl;
		inputGate->setValue(newValue);

		this->circuitDrawing.push_back( std::vector<std::string>() );
		std::string gateValue = (inputGate->getValue()) ? "1" : "0";
		this->circuitDrawing.at(i).push_back( std::string(1, inputGate->getName()) + ":" + gateValue + " ");
		//this->circuitDrawing.at(i).push_back(std::string(1, inputGate->getValue()));
		//this->circuitDrawing.at(i).push_back(" ");
		i++;
	}

	bool circuitCompleted = false;

	while (!circuitCompleted) {
		circuitCompleted = true;

		// Updating the logical gates for which the inputs are ready (i.e. intpus are either InputGate or updated LogicalGate)
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
					std::cout << "Value of Gate \"" << logicalGate->getType() << "\" : " << logicalGate->getValue() << std::endl;


					// Adding the gate to the drawing
					logicalGate->updateLevel();

					// gateLine = number of input gates + gate level * LEVEL_HEIGHT - 1
					unsigned int gateLine = this->getInputGates().size() + logicalGate->getGateLevel() * Circuit::LEVEL_HEIGHT - 1;

					// Add one level to the drawing if necessary
					if (gateLine > this->getCircuitDrawing().size()) {
						for (int i = 0; i < Circuit::LEVEL_HEIGHT; i++) {
							this->circuitDrawing.push_back( std::vector<std::string>());
						}
					}

					// Add one 'depth' to the level (the fist column being larger)
					for (unsigned int i = gateLine;  i > gateLine - Circuit::LEVEL_HEIGHT + 1; i--) {
						for (int j = 0; j < Circuit::GATE_WIDTH; j++) {
							if(this->circuitDrawing.at(i).size() == 0) { this->circuitDrawing.at(i).push_back("    "); }
							else { this->circuitDrawing.at(i).push_back(" "); }
						}
					}

					// gateDepth = number of columns / GATE_WIDTH
					int gateColumn = this->getCircuitDrawing().at(gateLine).size() - 1;
					int gateDepth = (gateColumn + 1) / Circuit::GATE_WIDTH ;
					logicalGate->setGateDepth(gateDepth);


					// Add the name of the gate to the drawing
					std::string gateName = "";
					gateName = gateName + logicalGate->getType();

					for (int i = 0; i < 3; i++) {
						this->circuitDrawing
							.at(gateLine - (int)std::floor(Circuit::LEVEL_HEIGHT / 2))
							.at(gateColumn - (int)std::floor(Circuit::GATE_WIDTH / 2) - 1 + i)
							= gateName[i];
					}

					// Add the "wires" between the gates
					int gateNumber = 0;
					for (Gate* gate : logicalGate->getGates()) {
						this->addWire(gate, logicalGate, gateNumber);
						gateNumber = gateNumber + 1;
					}


					// Display the current circuit on screen
					this->printCircuit();


					// Press any key to continue (actually 1 key + enter)
					std::cout << "Press any key then enter to update the next gate.";

					std::string anyKey;
					std::cin >> anyKey;
					std::cout << std::endl;
				}
			}
		}
	}

	// Updating the value of the outputs
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


void Circuit::addWire(Gate* const prevGate, Gate* const nextGate, const int gateNumber) {
	unsigned int column = 0;
	unsigned int line = 0;

	// debug
	std::cout << "prevGate type, level, depth : " << prevGate->getType()
		<< ", " << prevGate->getGateLevel()
		<< ", " << prevGate->getGateDepth() << std::endl;


	std::cout << "nextGate type, level, depth : " << nextGate->getType()
		<< ", " << nextGate->getGateLevel()
		<< ", " << nextGate->getGateDepth() << std::endl;
	// fin debug


	if (prevGate->getType() == GateType::INPUT) {
		line = prevGate->getGateLevel();
		unsigned int wireColumnMax = nextGate->getGateDepth() * Circuit::GATE_WIDTH - (int) std::ceil(Circuit::GATE_WIDTH / 2) +  gateNumber * 2;
		unsigned int wireLineMax = nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT / 2);

		std::cout << "colonne : " << wireColumnMax << std::endl; // debug

		// Horizontal line coming from the input
		for (column = 2; column < wireColumnMax; column++) {
			if (column >= this->circuitDrawing.at(line).size()) {
				this->circuitDrawing.at(line).push_back("-");
			}
			else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
				this->circuitDrawing.at(line).assign(column, "+");
			}
			//else { this->circuitDrawing.at(prevGate->getGateLevel()).at(line) = "-"; }
		}

		// Adding the sign * when there is a change of direction
		if (column >= this->circuitDrawing.at(line).size()) {
			this->circuitDrawing.at(line).push_back("*");
		}
		else { this->circuitDrawing.at(line).at(column) = "*"; }


		for (line; line < wireLineMax; line++) {
			if (this->circuitDrawing.at(line).at(column).compare("-") == 0) {
				this->circuitDrawing.at(line).assign(column, "+");
			}
			else{ this->circuitDrawing.at(line).assign(column, "|"); }
		}
	}
}


void Circuit::printCircuit() {
	for ( std::vector<std::string> line : this->getCircuitDrawing()) {
		for (std::string column : line) {
			std::cout << column;
		}
		std::cout << std::endl;
	}
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

const std::vector<std::vector<std::string>>& Circuit::getCircuitDrawing() const { return this->circuitDrawing; }

const std::vector<int>& Circuit::getDepthPerLevel() const { return this->depthPerLevel; }
