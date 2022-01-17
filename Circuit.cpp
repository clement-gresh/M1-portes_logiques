#include "Circuit.hpp"

// CONSTRUCTORS
Circuit::Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*>& logicalGates,
				 std::vector<OutputGate*>& outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates }, drawing{ inputGates.size() } {}

Circuit::~Circuit(){
	for (InputGate* ig : this->inputGates) { delete ig; }
	for (LogicalGate* lg : this->logicalGates) { delete lg; }
	for (OutputGate* og : this->outputGates) { delete og; }
	this->inputGates.clear();
	this->logicalGates.clear();
	this->outputGates.clear();
	std::vector<InputGate*>().swap(this->inputGates);
	std::vector<LogicalGate*>().swap(this->logicalGates);
	std::vector<OutputGate*>().swap(this->outputGates);
}

// METHODS
void Circuit::simulateCircuit() {
	// Reinitializing the circuit
	for (LogicalGate* gate : this->getLogicalGates()) {
		gate->setAlreadyUpdated(false);
	}

	// Assigning a value to each input and adding them to the drawing
	int line = 0;
	for (InputGate* inputGate : this->getInputGates()) {
		// Asking the user to set a value to the input
		std::string s1 = "Please enter the value of Gate \"";
		s1.push_back(inputGate->getName());
		s1 = s1 + "\" (0 / 1) : ";
		std::string newValue = parser::userInput(s1, std::regex{ "^[01]$" } );

		if (newValue.compare("0") == 0) { inputGate->setValue(0); }
		else { inputGate->setValue(1); }
		std::cout << inputGate->getName() << " : " << inputGate->getValue() << std::endl << std::endl;

		// Updating the drawing
		inputGate->setGateLine(line);
		inputGate->setGateColumn(0);
		inputGate->drawGate(this->drawing);
		line = line + 1;
	}

	//debug
	std::cout << "-----------------------INPUTS-----------------------" << std::endl << std::endl;
	this->drawing.print();
	//fin debug

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
					std::cout << "---------------------------------------------------------" << std::endl << std::endl;
					std::cout << logicalGate;


					// Updating the drawing
					this->drawing.findCoordinates(logicalGate);
					logicalGate->drawGate(this->drawing);
					this->drawing.addWire(logicalGate);
					this->drawing.print();

					// Press enter to continue
					std::cout << "Press enter to update the next gate.";
					std::cin.ignore(1000, '\n');
					std::cout << std::endl;
				}
			}
		}
	}

	// Updating the value of the outputs
	for (OutputGate* outputGate : this->getOutputGates()) {
		outputGate->updateGate();
		this->drawing.findCoordinates(outputGate);
		outputGate->drawGate(this->drawing);
		this->drawing.addWire(outputGate);
		std::cout << outputGate;
	}

	std::cout << "-----------------------OUTPUTS-----------------------" << std::endl << std::endl;
	this->drawing.print();

	// Saving the circuit in a file
	std::string s = "Do you want to save this circuit in a file? (y/n) ";
	std::string save = parser::userInput(s, std::regex{ "^[yn]$" });
	if (save.compare("y") == 0) { this->saveFile(); }
}

void Circuit::saveFile() {

	std::string s = "Save as (enter the name of the file without the extension) : ";
	std::string save = parser::userInput(s, std::regex{ "^[/.//_0-9a-zA-Z-]+$" });

	std::ofstream output_file;
	output_file.open(save + ".txt");

	for (OutputGate* outputGate : this->getOutputGates()) { 
		output_file << outputGate->getLogicalFunction() << "\n";
		output_file.flush();
	}

	for (std::vector<std::string> line : this->drawing.getDrawingArray()) {
		for (std::string column : line) {
			output_file << column;
			output_file.flush();
		}
		output_file << std::endl;
		output_file.flush();
	}
	output_file.close();
}

// ACCESSORS
const std::vector<InputGate*>& Circuit::getInputGates() const { return this->inputGates; }
const std::vector<LogicalGate*>& Circuit::getLogicalGates() const { return this->logicalGates; }
const std::vector<OutputGate*>& Circuit::getOutputGates() const { return this->outputGates; }
const Drawing Circuit::getDrawing() const { return this->drawing; }
