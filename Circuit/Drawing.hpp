#ifndef DRAWING
#define DRAWING

#include <string>
#include <regex>
#include <iostream>

class OutputGate;
class LogicalGate;
class Gate;

class Drawing{
	friend class Circuit;

private:
	static const int GATE_HEIGHT;
	static const int GATE_WIDTH; // Has to be an even number
	const unsigned int inputNumber;
	unsigned int height;
	unsigned int width;
	std::vector <std::vector <std::string>> drawingArray;

	// CONSTRUCTORS
	Drawing(const Drawing& clone);
	Drawing(const Drawing* clone);
	Drawing();
	Drawing(const unsigned int inputNumber);

	// METHODS
	void addLine(int nbr);
	void addColumn(int nbr);
	void findCoordinates(LogicalGate* const lg);
	void findCoordinates(OutputGate* const og);
	void addWire(const LogicalGate* const lg);
	void addWire(const OutputGate* const lg);
	void drawVLine(int column, int lineBegin, int lineEnd);
	void drawHLine(int line, int columnBegin, int columnEnd);
	void reinitialize();

public:
	void draw(int line, int column, std::string s);
	void print();

	// ACCESSORS
	const unsigned int getInputNumber() const;
	const unsigned int getHeight() const;
	const unsigned int getWidth() const;
	const std::vector <std::vector <std::string>> getDrawingArray() const;
};

#endif

