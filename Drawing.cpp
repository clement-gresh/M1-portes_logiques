#include "Drawing.hpp"
#include "LogicalGate.hpp"
#include "OutputGate.hpp"


// STATIC ATTRIBUTES
const int Drawing::GATE_HEIGHT{ 9 };
const int Drawing::GATE_WIDTH{ 12 };

// CONSTRUCTORS
Drawing::Drawing(const Drawing& clone) : inputNumber{ clone.getInputNumber() }, height{ clone.getHeight() },
					width{ clone.getWidth() }, drawingArray{ clone.getDrawingArray() } {
	std::cout << "Attention : construction d'un dessin par COPIE (reference) !" << std::endl;
}

Drawing::Drawing(const Drawing* clone) : inputNumber{ clone->getInputNumber() }, height{ clone->getHeight() },
					width{ clone->getWidth() }, drawingArray{ clone->getDrawingArray() } {
	std::cout << "Attention : construction d'un dessin par COPIE (pointeur) !" << std::endl;
}

Drawing::Drawing() : inputNumber{ 0 }, height{ 0 }, width{ 0 }, drawingArray{ std::vector <std::vector <std::string>>() } {
	std::cout << "Attention : construction d'un dessin par defaut !" << std::endl;
}

Drawing::Drawing(int const inputNumber) : inputNumber{ inputNumber }, height{ inputNumber }, width{ 1 },
		drawingArray{ std::vector <std::vector <std::string>>(inputNumber, std::vector <std::string>(GATE_WIDTH, " ")) } {}


// METHODS
// Adds a certain number of lines to the drawing
void Drawing::addLine(int nbr){
	for (int i = 0; i < nbr; i++) {
		this->height = this->height + 1;
		this->drawingArray.push_back({" "});

		for (int j = 1; j < this->width; j++) {
			this->drawingArray.at(this->height - 1).push_back(" ");
		}
	}
}

// Adds a certain number of columns to the drawing
void Drawing::addColumn(int nbr) {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < nbr; j++) {
			this->drawingArray.at(i).push_back(" ");
		}
	}
	this->width = this->width + nbr;
}

// Finds the line and column of the logical gate (and adds lines and columns to the drawing if necessary)
void Drawing::findCoordinates(LogicalGate* const lg){
	// Line
	int max = this->inputNumber - 1;
	for (const Gate* gate : lg->getGates()) {
		if (gate->getGateLine() > max)
			max = gate->getGateLine();
	}
	if (max + GATE_HEIGHT > this->height) { this->addLine(GATE_HEIGHT); }
	lg->setGateLine(max + GATE_HEIGHT);

	// Column
	// If one of the input gates is an input, adds a column to the drawing and puts the logical gate there
	float average = 0;
	int number = 0;
	for (Gate* gate : lg->getGates()) {
		if (gate->getGateColumn() == 0) {
			this->addColumn(GATE_WIDTH);
			lg->setGateColumn(this->width - 5);
			break;
		}
		number = number + 1;
		average = average + (gate->getGateColumn() - average) / number;
	}
	// Else, the gate column is between the input gates (if no other gate is already there)
	if (number == lg->getGates().size()) {
		int column = static_cast<int>(average);
		bool found = false;

		while (!found) {
			// Checking that 7 consecutive cells are empty
			if (column + 5 > this->width) { this->addColumn(GATE_WIDTH); }

			for (int i = -3; i < 4; i++) {
				std::string content = this->drawingArray.at(lg->getGateLine()).at(column + i);
				found = true;

				if (std::regex_match(content, std::regex{ "^[a-zA-Z0-9_-]$" })) {
					found = false;
					break;
				}
			}
			if (!found) { column = column + GATE_WIDTH; }
		}
		lg->setGateColumn(column);
	}
}

// Finds the line and column of the output gate (and adds lines and columns to the drawing if necessary)
void Drawing::findCoordinates(OutputGate* const og){
	// Column
	int column = og->getGate()->getGateColumn();
	if (column == 0) {
		og->setGateColumn(GATE_WIDTH - 5);
		if (this->width < GATE_WIDTH) { this->addColumn(GATE_WIDTH); }
	}
	else { og->setGateColumn(column); }

	// Line
	int line = og->getGate()->getGateLine();

	if (line < this->inputNumber) {
		line = this->inputNumber + GATE_HEIGHT - 2;
		og->setGateLine(line);
	}
	else{
		line = line + GATE_HEIGHT - 2;
		og->setGateLine(line);
	}
	if (line + 2 > this->height) { this->addLine(GATE_HEIGHT); }
}

// Adds the "wires" between the logical gate and its input(s)
void Drawing::addWire(LogicalGate* const lg){
	int offsetC = -1;
	int gateNumber = 1;
	int arrivalLine = lg->getGateLine() - 1;

	for (const Gate* gate : lg->getGates()) {
		int arrivalColumn = lg->getGateColumn() + offsetC;
		int column = gate->getGateColumn();
		int line = gate->getGateLine();

		// Starts with a vertical line coming from the gate (if its not an input)
		if (line > this->inputNumber) {
			int offsetL = column / GATE_WIDTH;
			this->drawVLine(column, line + 1, line + offsetL + 1);
			line = line + offsetL + 2;
			this->draw(line, column, "*");
		}

		// Then an horizontal line
		int columnDifference = arrivalColumn - column;
		int lineDifference = arrivalLine - line;

		if (columnDifference != 0) {
			if (columnDifference > 0) { this->drawHLine(line, column + 1, arrivalColumn - 1); }
			else {
				// If the first input is on the right of the gate, then it gets connected to the right "entrance" of the gate
				if (gateNumber == 1) {
					arrivalColumn = arrivalColumn + 2;
					offsetC = -3;
				}
				this->drawHLine(line, arrivalColumn + 1, column - 1);
			}

			this->draw(line, arrivalColumn, "*");
			line = line + 1;
			gateNumber = gateNumber + 1;
		}

		// Then a vertical line
		this->drawVLine(arrivalColumn, line, arrivalLine);

		offsetC = offsetC + 2;
	}	
}


// Adds the "wires" between the ouptut gate and its input
void Drawing::addWire(OutputGate* const og){
	int arrivalLine = og->getGateLine();
	int arrivalColumn = og->getGateColumn();
	int line = og->getGate()->getGateLine();
	int column = og->getGateColumn();

	// Starts with an horizontal line coming from the gate (if its an input)
	if (line < this->inputNumber) {
		this->drawHLine(line, column + 1, arrivalColumn - 1);
		this->draw(line, arrivalColumn, "*");
	}

	// Then a vertical line
	this->drawVLine(arrivalColumn, line + 1, arrivalLine - 1);
}

// Draws a vertical line
void Drawing::drawVLine(int column, int lineBegin, int lineEnd){
	for (int line = lineBegin; line <= lineEnd; line++) {
		if (this->drawingArray.at(line).at(column).compare("-") == 0) {
			this->draw(line, column, "+");
		}
		else if (this->drawingArray.at(line).at(column).compare(" ") == 0) {
			this->draw(line, column, "|");
		}
	}
}

// Draws an horizontal line
void Drawing::drawHLine(int line, int columnBegin, int columnEnd){
	for (int column = columnBegin; column <= columnEnd; column++) {
		if (this->drawingArray.at(line).at(column).compare("|") == 0) {
			this->draw(line, column, "+");
		}
		else if (this->drawingArray.at(line).at(column).compare(" ") == 0) {
			this->draw(line, column, "-");
		}
	}
}

// Draws a string on a specifi cell
void Drawing::draw(int line, int column, std::string s){
	this->drawingArray.at(line).at(column) = s;
}

// Prints the current drawing on the screen
void Drawing::print(){
	std::cout << std::endl ;
	for (const std::vector<std::string> line : this->drawingArray) {
		for (const std::string column : line) {
			std::cout << column;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}


// ACCESSORS
const int Drawing::getInputNumber() const { return this->inputNumber; }
const int Drawing::getHeight() const { return this->height; }
const int Drawing::getWidth() const { return this->width; }
const std::vector<std::vector<std::string>> Drawing::getDrawingArray() const { return this->drawingArray; }
