#ifndef GATE
#define GATE

#include <string>
#include <regex>
#include <iostream>

class Gate {
protected:
	bool value;
	bool alreadyUpdated;
	int gateLevel;
	int gateDepth;
	std::string logicalFunction;

	// CONSTRUCTORS
	Gate();
	Gate(const Gate& clone);
	Gate(const Gate* clone);

	// ACCESSORS
	void setValue(const bool value);
	void setLogicalFunction(const std::string function);

public:
	const bool getValue() const;
	const bool getAlreadyUpdated() const;
	const int getGateLevel() const;
	const int getGateDepth() const;
	const std::string getLogicalFunction() const;

	void setAlreadyUpdated(const bool alreadyUpdated);
	void setGateLevel(const int level);
	void setGateDepth(const int depth);
};


#endif