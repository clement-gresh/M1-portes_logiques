#include "Circuit.hpp"

// INITIALIZATION of constant static members
const int Circuit::LEVEL_HEIGHT{ 5 };
const int Circuit::GATE_WIDTH{ 5 };


// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates },
	circuitDrawing{ std::vector<std::vector<std::string>>() }, depthPerLevel{ {1} } {}


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
		bool newValue;

		std::cout << "Please enter the value of Gate \"" << inputGate->getName() << "\" (0 / 1) : ";

		std::cin >> newValue;
		inputGate->setValue(newValue);
		std::cout << inputGate->getName() << " : " << newValue << std::endl;
		std::cin.ignore(1000, '\n');


		std::vector<std::string> newLine = { std::string(1, inputGate->getName()) + ":" + std::string(1, inputGate->getValue()) + " " };
		for (int j = 1; j < Circuit::GATE_WIDTH; j++) newLine.push_back(" ");
		this->circuitDrawing.push_back( newLine );

		i = i + 1;
	}


	// Updating the logical gates and adding them to the drawing
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

					// Calculating the level and line of the gate
					logicalGate->updateLevel();
					int gateLevel = logicalGate->getGateLevel();

					// gateLine = number of input gates + gate level * LEVEL_HEIGHT - 1
					unsigned int gateLine = this->getInputGates().size() + gateLevel * Circuit::LEVEL_HEIGHT - 1;

					int maxDepth = this->getDepthPerLevel().at(0);


					// Adding one level to the drawing if necessary (the fist column being larger)
					if (gateLine > this->getCircuitDrawing().size()) {
						for (int i = 0; i < Circuit::LEVEL_HEIGHT; i++) {

							std::vector<std::string> newLine{ "    " };
							for (int j = 1; j < Circuit::GATE_WIDTH * maxDepth; j++) newLine.push_back(" ");
							this->circuitDrawing.push_back(newLine);
						}
						this->depthPerLevel.push_back(0);
					}


					// Calculating the depth, and column of the gate
					int gateDepth = this->getDepthPerLevel().at(gateLevel) + 1;
					logicalGate->setGateDepth(gateDepth);
					this->depthPerLevel.at(gateLevel) = gateDepth;

					// Adding one 'depth' to the whole drawing if necessary
					if (gateDepth > maxDepth) {
						this->depthPerLevel.at(0) = gateDepth;
						maxDepth = gateDepth;

						for (unsigned int i = 0; i < this->getCircuitDrawing().size(); i++) {
							for (int j = 0; j < Circuit::GATE_WIDTH; j++) this->circuitDrawing.at(i).push_back(" ");
						}
					}



					// Add the name of the gate to the drawing
					std::string gateName = "";
					gateName = gateName + logicalGate->getType();

					int gateColumn = gateDepth * Circuit::GATE_WIDTH - 1;

					for (int i = 0; i < 3; i++) {
						this->circuitDrawing
							.at(gateLine - (int)std::floor(Circuit::LEVEL_HEIGHT / 2.))
							.at(gateColumn - (int)std::floor(Circuit::GATE_WIDTH / 2.) + i)
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


					// Press enter to continue
					std::cout << "Press enter to update the next gate.";
					std::cin.ignore(1000, '\n');
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
	/*
	std::cout << "prevGate type, level, depth : " << prevGate->getType()
		<< ", " << prevGate->getGateLevel()
		<< ", " << prevGate->getGateDepth() << std::endl;


	std::cout << "nextGate type, level, depth : " << nextGate->getType()
		<< ", " << nextGate->getGateLevel()
		<< ", " << nextGate->getGateDepth() << std::endl;
	*/
	// fin debug


	if (prevGate->getType() == GateType::INPUT) {
		line = prevGate->getGateLevel();

		unsigned int arrivalColumn = nextGate->getGateDepth() * Circuit::GATE_WIDTH - (int) std::ceil(Circuit::GATE_WIDTH / 2.) +  gateNumber * 2;
		unsigned int arrivalLine = this->getInputGates().size() + nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT / 2.);

		// Horizontal line coming from the input
		for (column = 1; column < arrivalColumn; column++) {
			
			if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) {
				this->circuitDrawing.at(line).at(column) = "-";
			}
			else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
				this->circuitDrawing.at(line).at(column) = "+";
			}
		}


		// Adding the sign * when there is a change of direction
		 this->circuitDrawing.at(line).at(column) = "*";
		 line = line + 1;


		// Vertical line going to the gate
		for (line; line < arrivalLine; line++) {

			if (this->circuitDrawing.at(line).at(column).compare("-") == 0) {
				this->circuitDrawing.at(line).at(column) = "+";
			}
			else{ this->circuitDrawing.at(line).at(column) = "|"; }
		}
	}

	else {
		column = prevGate->getGateDepth() * Circuit::GATE_WIDTH - (int)std::floor(Circuit::GATE_WIDTH / 2.);
		line = this->getInputGates().size() + prevGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::floor(Circuit::LEVEL_HEIGHT / 2.);

		unsigned int arrivalColumn = nextGate->getGateDepth() * Circuit::GATE_WIDTH - (int)std::ceil(Circuit::GATE_WIDTH / 2.) + gateNumber * 2;
		unsigned int arrivalLine = this->getInputGates().size() + nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT / 2.);

		int columnDifference = arrivalColumn - column;
		int lineDifference = arrivalLine - line;

		std::cout << "colonne max : " << arrivalColumn << std::endl; // debug
		std::cout << "ligne max : " << arrivalLine << std::endl; // debug

		std::cout << "colonne diff : " << columnDifference << std::endl; // debug
		std::cout << "ligne diff : " << lineDifference << std::endl; // debug


		// Vertical line coming from the previsou gate
		for (line; line < arrivalLine - lineDifference / 2; line++) {

			if (this->circuitDrawing.at(line).at(column).compare("-") == 0) {
				this->circuitDrawing.at(line).at(column) = "+";
			}
			else { this->circuitDrawing.at(line).at(column) = "|"; }
		}

		// Horizontal line coming from the previous gate
		if (columnDifference > 0) {
			for (column; column < arrivalColumn - columnDifference / 2; column++) {


				std::cout << "colonne : " << column << ", ligne : " << line << std::endl; // debug

				if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) {
					this->circuitDrawing.at(line).at(column) = "-";
				}
				else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
					this->circuitDrawing.at(line).at(column) = "+";
				}
			}
		}

		else if (columnDifference < 0) {
			for (column; column > arrivalColumn + columnDifference / 2; column--) {

				if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) {
					this->circuitDrawing.at(line).at(column) = "-";
				}
				else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
					this->circuitDrawing.at(line).at(column) = "+";
				}
			}
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
