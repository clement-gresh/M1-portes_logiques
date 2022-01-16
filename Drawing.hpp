#ifndef DRAWING
#define DRAWING

#include "LogicalGate.hpp"


class Drawing{
private:
	static const int GATE_HEIGHT;
	static const int GATE_WIDTH; // Has to be an even number
	int inputNumber;
	int height;
	int width;
	std::vector <std::vector <std::string>> drawingArray;

public:
	// CONSTRUCTORS
	Drawing(int const inputNumber);

	// METHODS
	void addLine(int nbr);
	void addColumn(int nbr);
	void findCoordinates(LogicalGate* const lg);
	void draw(int line, int column, std::string s);
	void print();
};

#endif