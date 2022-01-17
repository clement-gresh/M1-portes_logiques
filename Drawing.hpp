#ifndef DRAWING
#define DRAWING

#include "LogicalGate.hpp"
#include "OutputGate.hpp"

class OutputGate;

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
	void findCoordinates(OutputGate* const og);
	void addWire(LogicalGate* const lg);
	void addWire(OutputGate* const lg);
	void drawVLine(int column, int lineBegin, int lineEnd);
	void drawHLine(int line, int columnBegin, int columnEnd);
	void draw(int line, int column, std::string s);
	void print();
};

#endif