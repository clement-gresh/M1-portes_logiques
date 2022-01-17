#include "Drawing.hpp"

const int Drawing::GATE_HEIGHT{ 9 };
const int Drawing::GATE_WIDTH{ 10 };

Drawing::Drawing(int const inputNumber) : inputNumber{inputNumber}, height { inputNumber }, width{ 1 },
					 drawingArray{ std::vector <std::vector <std::string>>(inputNumber, std::vector <std::string>(1, ""))} {}

void Drawing::addLine(int nbr){
	for (int i = 0; i < nbr; i++) {
		this->height = this->height + 1;
		this->drawingArray.push_back({"    "});

		for (int j = 1; j < this->width; j++) {
			this->drawingArray.at(this->height - 1).push_back(" ");
		}
	}
}

void Drawing::addColumn(int nbr) {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < nbr; j++) {
			this->drawingArray.at(i).push_back(" ");
		}
	}
	this->width = this->width + nbr;
}

// Finds the line and column of the gates (and add lines and columns to the drawing if necessary)
void Drawing::findCoordinates(LogicalGate* const lg){
	// Line
	int max = this->inputNumber - 1;
	for (Gate* gate : lg->getGates()) {
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
			lg->setGateColumn(this->width - 3);
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
			// Checking that 5 consecutive cells are empty
			if (column + 3 > this->width) { this->addColumn(GATE_WIDTH); }

			for (int i = -2; i < 3; i++) {
				std::cout << i << " " << column + i << ", "; //debug
				std::string content = this->drawingArray.at(lg->getGateLine()).at(column + i);
				found = true;

				if (std::regex_match(content, std::regex{ "^[a-zA-Z0-9_-]$" })) {
					found = false;
					break;
				}
			}
			if (!found) { column = column + GATE_WIDTH / 2; }
		}
		lg->setGateColumn(column);
	}
}

void Drawing::addWire(LogicalGate* const lg){
	int offset = -1;
	int arrivalLine = lg->getGateLine() - 1;

	for (Gate* gate : lg->getGates()) {
		int arrivalColumn = lg->getGateColumn() + offset;
		int column = gate->getGateColumn();
		int line = gate->getGateLine();

		// Starts with a vertical line coming from the gate (if its not an input)
		if (line > this->inputNumber) {
			this->drawVLine(column, line + 1, line + 3);
			this->draw(line + 4, column, "*");
			line = line + 4;
		}

		// Then an horizontal line
		int columnDifference = arrivalColumn - column;
		int lineDifference = arrivalLine - line;

		if (columnDifference != 0) {
			if (columnDifference > 0) { this->drawHLine(line, column + 1, arrivalColumn - 1); }
			else { this->drawHLine(line, arrivalColumn + 1, column - 1); }

			this->draw(line, arrivalColumn, "*");
			line = line + 1;
		}

		// Then a vertical line
		this->drawVLine(arrivalColumn, line, arrivalLine);

		offset = offset + 2;
	}	
}

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

void Drawing::draw(int line, int column, std::string s){
	this->drawingArray.at(line).at(column) = s;
}

void Drawing::print(){
	std::cout << std::endl ;
	for (std::vector<std::string> line : this->drawingArray) {
		for (std::string column : line) {
			std::cout << column;
		}
		std::cout << std::endl;
	}
}
