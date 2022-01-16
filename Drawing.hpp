#ifndef DRAWING
#define DRAWING

#include "Gate.hpp"

class Drawing{
private:
	static const int GATE_HEIGHT;
	static const int GATE_WIDTH;
	int height;
	int width;
	std::vector <std::vector <std::string>> drawingArray;

public:
	// CONSTRUCTORS
	Drawing();

	// METHODS
	void addLine(int nbr);
	void addColumn(int nbr);
	void draw(int line, int column, std::string s);
	void print();
};

#endif