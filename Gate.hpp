#ifndef GATE
#define GATE

#include "GateType.hpp"

#include <string>
#include <regex>


class Gate {
protected:
	bool value;
	const GateType type;
	bool alreadyUpdated;
	int gateLevel;
	int gateDepth;
	std::string logicalFunction;

	// CONSTRUCTORS
	Gate(const GateType type);
	Gate(const Gate& clone);
	Gate(const Gate* clone);

	// ACCESSORS
	void setValue(const bool value);
	void setLogicalFunction(const std::string function);

public:
	const bool getValue() const;
	const GateType getType() const;
	const bool getAlreadyUpdated() const;
	const int getGateLevel() const;
	const int getGateDepth() const;
	const std::string getLogicalFunction() const;

	void setAlreadyUpdated(const bool alreadyUpdated);
	void setGateLevel(const int level);
	void setGateDepth(const int depth);
};


#endif