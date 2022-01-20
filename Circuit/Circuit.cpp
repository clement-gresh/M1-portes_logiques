#include "Circuit.hpp"

// CONSTRUCTORS
// private
Circuit::Circuit() : inputGates{ std::vector<InputGate*>() }, logicalGates{ std::vector<LogicalGate*>() },
					outputGates{ std::vector<OutputGate*>() }, drawing{ 1 }{}

// public
Circuit::Circuit(const Circuit& clone) : Circuit{ clone.getInputGates(), clone.getLogicalGates(), clone.getOutputGates() } {}
Circuit::Circuit(const Circuit* clone) : Circuit{ clone->getInputGates(), clone->getLogicalGates(), clone->getOutputGates() } {}

Circuit::Circuit(const std::vector<InputGate*>& inputGates, const std::vector<LogicalGate*>& logicalGates,
				 const std::vector<OutputGate*>& outputGates)
	: inputGates{ inputGates }, logicalGates{ logicalGates }, outputGates{ outputGates }, drawing{ static_cast<unsigned int>(inputGates.size()) } {}

// DESTRUCTOR
Circuit::~Circuit(){
	for (InputGate* ig : this->inputGates) { delete ig; }
	for (LogicalGate* lg : this->logicalGates) { delete lg; }
	for (OutputGate* og : this->outputGates) { delete og; }
}

// METHODS
// Updates all the gates composing the circuit and displays them on the screen
void Circuit::simulateCircuit() {
	// Reinitializing the circuit
	this->drawing.reinitialize();
	for (LogicalGate* gate : this->getLogicalGates()) {
		gate->setAlreadyUpdated(false);
	}

	// Assigning a value to each input and adding them to the drawing
	std::cout << std::endl << "----------------------------------INPUTS----------------------------------" << std::endl << std::endl;
	int line = 0;
	for (InputGate* inputGate : this->getInputGates()) {
		// Asking the user to set a value to the input
		std::string s1 = "Please enter the value of Gate \"";
		s1.push_back(inputGate->getName());
		s1 = s1 + "\" (0 / 1) : ";
		std::string newValue = parser::userInput(s1, std::regex{ "^[01]$" } );

		inputGate->setValue( (newValue.compare("0") == 0) ? 0 : 1 );
		std::cout << inputGate->getName() << " : " << inputGate->getValue() << std::endl << std::endl;

		// Updating the drawing
		inputGate->setGateLine(line);
		inputGate->setGateColumn(0);
		inputGate->drawGate(this->drawing);
		line = line + 1;
	}

	// Updating the logical gates and adding them to the drawing
	bool circuitCompleted = false;
	unsigned int counter = 0;

	while (!circuitCompleted) {
		if (counter > this->getLogicalGates().size()) {
			throw std::invalid_argument{"Invalid list of logical gates : the program cannot end."};
		}
		circuitCompleted = true;

		// Updating the logical gates for which the inputs are ready (i.e. intpus are either InputGate or updated LogicalGate)
		for (LogicalGate* logicalGate : this->getLogicalGates()) {
			if (!logicalGate->getAlreadyUpdated()) {
				bool canBeUpdated = true;

				for (const Gate* input : logicalGate->getGates()) {
					if (!input->getAlreadyUpdated()) {
						canBeUpdated = false;
						circuitCompleted = false;
					}
				}

				if (canBeUpdated) {
					std::cout << "---------------------------------------------------------------------------" << std::endl << std::endl;
					// Press enter to continue
					std::cout << "Press enter to update the next gate.";
					std::cin.ignore(1000, '\n');
					std::cout << std::endl;

					// Updating the gate (its logical function and value)
					logicalGate->updateGate();
					logicalGate->setAlreadyUpdated(true);
					std::cout << logicalGate;

					// Updating the drawing
					this->drawing.findCoordinates(logicalGate);
					logicalGate->drawGate(this->drawing);
					this->drawing.addWire(logicalGate);
					this->drawing.print();
				}
			}
		}
		counter = counter + 1;
	}
	// Updating the value of the outputs
	std::cout << "----------------------------------OUTPUTS----------------------------------" << std::endl << std::endl;
	// Press enter to continue
	std::cout << "Press enter to update the outputs.";
	std::cin.ignore(1000, '\n');
	std::cout << std::endl;

	for (OutputGate* outputGate : this->getOutputGates()) {
		if (std::find(this->getInputGates().begin(), this->getInputGates().end(), outputGate->getGate())
			== this->getInputGates().end()
			&& std::find(this->getLogicalGates().begin(), this->getLogicalGates().end(), outputGate->getGate())
			== this->getLogicalGates().end())
		{
			throw std::invalid_argument{ "Invalid list of gates. The program cannot end because the input of the following output gate is not present : "
				+ std::string(1, outputGate->getName()) };
		}
		outputGate->updateGate();
		this->drawing.findCoordinates(outputGate);
		outputGate->drawGate(this->drawing);
		this->drawing.addWire(outputGate);
		std::cout << outputGate;
	}

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

	for (const OutputGate* outputGate : this->getOutputGates()) { 
		output_file << outputGate->getLogicalFunction() << "\n";
		output_file.flush();
	}
	output_file << std::endl << std::endl;
	output_file.flush();

	for (const std::vector<std::string> line : this->drawing.getDrawingArray()) {
		for (const std::string column : line) {
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
const Drawing& Circuit::getDrawing() const { return this->drawing; }
