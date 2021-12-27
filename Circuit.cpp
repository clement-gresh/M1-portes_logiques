#include "Circuit.hpp"

// INITIALIZATION of constant static members
const int Circuit::LEVEL_HEIGHT{ 9 };
const int Circuit::GATE_WIDTH{ 7 };


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

		// Asking the user to set a value to the input (and checking that value is valid)
		std::cout << "Please enter the value of Gate \"" << inputGate->getName() << "\" (0 / 1) : ";
		std::string newValue;
		std::cin >> newValue;

		while (newValue.compare("0") != 0 && newValue.compare("1") != 0) {
			std::cout << "Invalid value! Please enter the value of Gate \"" << inputGate->getName() << "\" (0 / 1) : ";
			std::cin >> newValue;
		}
		std::cin.ignore(1000, '\n');

		if (newValue.compare("0") == 0) { inputGate->setValue(0); }
		else { inputGate->setValue(1); }
		std::cout << inputGate->getName() << " : " << inputGate->getValue() << std::endl << std::endl;


		// Adding the input to the drawing
		std::vector<std::string> newLine = { std::string(1, inputGate->getName()) + ":" + newValue + " " };
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
					// Updating the gate (its level, logical function and value)
					logicalGate->updateGate();
					logicalGate->setAlreadyUpdated(true);
					std::cout << logicalGate;


				// Adding the gate to the drawing
					// Calculating the level and line of the gate
					int gateLevel = logicalGate->getGateLevel();

					// gateLine = number of input gates + gate level * LEVEL_HEIGHT - 1
					unsigned int gateLine = this->getInputGates().size() + gateLevel * Circuit::LEVEL_HEIGHT - 1;

					this->addLevel(gateLine);


					// Calculating the depth and column of the gate
					int gateDepth = this->getDepthPerLevel().at(gateLevel) + 1;
					logicalGate->setGateDepth(gateDepth);
					this->depthPerLevel.at(gateLevel) = gateDepth;

					this->addDepth(gateDepth);


					// Adding the name of the gate to the drawing
					std::string gateName = "";
					gateName = gateName + logicalGate->getType();

					int gateColumn = gateDepth * Circuit::GATE_WIDTH - 1;

					for (int i = 0; i < 3; i++) {
						this->circuitDrawing
							.at(gateLine - (int)std::floor(Circuit::LEVEL_HEIGHT / 2.))
							.at(gateColumn - (int)std::floor(Circuit::GATE_WIDTH / 2.) + i)
							= gateName[i];
					}


					// Adding the "wires" between the gates
					int gateNumber = 0;
					for (Gate* gate : logicalGate->getGates()) {
						this->addWire(gate, logicalGate, gateNumber);
						gateNumber = gateNumber + 1;
					}


					// Displaying the current circuit on screen
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
		gate->updateGate();
		std::cout << gate;

	// Adding the output gate to the drawing
		// Calculating the level and line of the gate
		int gateLevel = gate->getGateLevel();

		// gateLine = number of input gates + gate level * LEVEL_HEIGHT - 1
		unsigned int gateLine = this->getInputGates().size() + gateLevel * Circuit::LEVEL_HEIGHT - 1;


		this->addLevel(gateLine);


		// Calculating the depth and column of the gate
		int gateDepth = gate->getGateDepth();

		this->addDepth(gateDepth);


		// Adding the name of the gate to the drawing
		int gateColumn = gateDepth * Circuit::GATE_WIDTH - 1;

		this->circuitDrawing
				.at(gateLine - (int)std::floor(Circuit::LEVEL_HEIGHT * 2. / 3.))
				.at(gateColumn - (int)std::floor(Circuit::GATE_WIDTH / 2.) + 1)
				= gate->getName();


		this->addWire(gate->getLogicalGate(), gate, 0);
	}

	// Displaying the final circuit on screen
	this->printCircuit();

	/* // debug : option 1
	for (OutputGate* outputGate : this->getOutputGates()) {

		LogicalGate* logicalGate = outputGate->getLogicalGate();
		
		nextGate(logicalGate);

		this->circuitGates.push_back(outputGate);
	}
	*/
}

// Add one level to the drawing if necessary (the fist column being larger)
void Circuit::addLevel(const unsigned int gateLine) {

	int maxDepth = this->getDepthPerLevel().at(0);

	if (gateLine > this->getCircuitDrawing().size()) {
		for (int i = 0; i < Circuit::LEVEL_HEIGHT; i++) {

			std::vector<std::string> newLine{ "    " };
			for (int j = 1; j < Circuit::GATE_WIDTH * maxDepth; j++) newLine.push_back(" ");
			this->circuitDrawing.push_back(newLine);
		}
		this->depthPerLevel.push_back(0);
	}
}


// Add one 'depth' to the whole drawing if necessary
void Circuit::addDepth(const int gateDepth) {

	int maxDepth = this->getDepthPerLevel().at(0);
	
	if (gateDepth > maxDepth) {
		this->depthPerLevel.at(0) = gateDepth;

		for (unsigned int i = 0; i < this->getCircuitDrawing().size(); i++) {
			for (int j = 0; j < Circuit::GATE_WIDTH; j++) this->circuitDrawing.at(i).push_back(" ");
		}
	}
}


void Circuit::addWire(Gate* const prevGate, Gate* const nextGate, const int gateNumber) {
	unsigned int column = 0;
	unsigned int line = 0;

	unsigned int arrivalColumn;
	unsigned int arrivalLine;
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

		arrivalColumn = nextGate->getGateDepth() * Circuit::GATE_WIDTH - (int) std::ceil(Circuit::GATE_WIDTH / 2.) +  gateNumber * 2;
		arrivalLine = this->getInputGates().size() + nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT / 2.);

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
	}

	else {
		column = prevGate->getGateDepth() * Circuit::GATE_WIDTH - (int)std::floor(Circuit::GATE_WIDTH / 2.);
		line = this->getInputGates().size() + prevGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::floor(Circuit::LEVEL_HEIGHT / 2.);


		if (nextGate->getType() != GateType::OUTPUT) {
			arrivalLine = this->getInputGates().size() + nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT / 2.);

			arrivalColumn = nextGate->getGateDepth() * Circuit::GATE_WIDTH - (int)std::ceil(Circuit::GATE_WIDTH / 2.) + gateNumber * 2;

			int columnDifference = arrivalColumn - column;
			int lineDifference = arrivalLine - line;

			/*
			std::cout << "colonne max : " << arrivalColumn << std::endl; // debug
			std::cout << "ligne max : " << arrivalLine << std::endl; // debug

			std::cout << "colonne diff : " << columnDifference << std::endl; // debug
			std::cout << "ligne diff : " << lineDifference << std::endl; // debug
			*/

			// Vertical line coming from the previous gate
			for (int i = 0; i < prevGate->getGateDepth(); i++) {
				this->circuitDrawing.at(line).at(column) = "|";
				line = line + 1;
			}

			// Horizontal line coming from the previous gate
			if (columnDifference != 0) {
				this->circuitDrawing.at(line).at(column) = "*";

				if (columnDifference > 0) {
					column = column + 1;

					for (column; column < arrivalColumn; column++) {

						//std::cout << "colonne : " << column << ", ligne : " << line << std::endl; // debug

						if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) {
							this->circuitDrawing.at(line).at(column) = "-";
						}
						else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
							this->circuitDrawing.at(line).at(column) = "+";
						}
					}
				}

				else if (columnDifference < 0) {
					column = column - 1;

					for (column; column > arrivalColumn; column--) {

						if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) {
							this->circuitDrawing.at(line).at(column) = "-";
						}
						else if (this->circuitDrawing.at(line).at(column).compare("|") == 0) {
							this->circuitDrawing.at(line).at(column) = "+";
						}
					}
				}

				this->circuitDrawing.at(line).at(column) = "*";
				line = line + 1;
			}
		}

		// if the next gate is an output, the wire is shorter (1/3 of LEVEL_HEIGHT instead of 1/2)
		else {
			arrivalLine = this->getInputGates().size() + nextGate->getGateLevel() * Circuit::LEVEL_HEIGHT - (int)std::ceil(Circuit::LEVEL_HEIGHT * 2. / 3.);
		}
	}

	// Vertical line going to the next gate
	for (line; line < arrivalLine; line++) {

		if (this->circuitDrawing.at(line).at(column).compare("-") == 0) {
			this->circuitDrawing.at(line).at(column) = "+";
		}
		else if (this->circuitDrawing.at(line).at(column).compare(" ") == 0) { 
			this->circuitDrawing.at(line).at(column) = "|";
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
