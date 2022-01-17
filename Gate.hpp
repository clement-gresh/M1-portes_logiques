#ifndef GATE
#define GATE

#include <string>
#include <regex>
#include <iostream>

class Drawing;

class Gate {
protected:
	bool value;
	bool alreadyUpdated;
	int gateLine;
	int gateColumn;
	std::string logicalFunction;

	// CONSTRUCTORS
	Gate();
	Gate(const Gate& clone);
	Gate(const Gate* clone);


	// ACCESSORS
	void setValue(const bool value);
	void setLogicalFunction(const std::string function);

public:	
	// METHODS
	virtual void drawGate(Drawing& d) = 0;

	// ACCESSORS
	const bool getValue() const;
	const bool getAlreadyUpdated() const;
	const int getGateLine() const;
	const int getGateColumn() const;
	const std::string getLogicalFunction() const;

	void setAlreadyUpdated(const bool alreadyUpdated);
	void setGateLine(const int level);
	void setGateColumn(const int depth);
};


#endif