#include "Drawing.hpp"

const int Drawing::GATE_HEIGHT{ 9 };
const int Drawing::GATE_WIDTH{ 10 };

Drawing::Drawing() : height{ 0 }, width{ 1 }, drawingArray{} {}

void Drawing::addLine(int nbr){
	for (int i = 0; i < nbr; i++) {
		this->drawingArray.push_back({"    "});
		this->height = this->height + 1;

		for (int j = 1; j < this->width; j++) {
			this->drawingArray.at(this->height - 1).push_back("l");
		}
	}
}

void Drawing::addColumn(int nbr) {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < nbr; j++) {
			this->drawingArray.at(i).push_back("c");
		}
	}
}

void Drawing::draw(int line, int column, std::string s){
	this->drawingArray.at(line).at(column) = s;
}

void Drawing::print(){
	for (std::vector<std::string> line : this->drawingArray) {
		for (std::string column : line) {
			std::cout << column;
		}
		std::cout << std::endl;
	}
}
