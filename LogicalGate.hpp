#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"

class LogicalGate : public Gate {
protected:
	const std::vector<Gate*> gates;
	bool alreadyUpdated;
	//const Gate* gate1;
	//const Gate* gate2;

	// CONSTRUCTORS
	LogicalGate(const std::vector<Gate*> gates);
	//LogicalGate(const Gate* gate1, const Gate* gate2);


public:
	// METHODS
	virtual void updateValue() {};

	// ACCESSORS
	const std::vector<Gate*> getGates() const;
	const bool getAlreadyUpdated() const;
	void setAlreadyUpdated(const bool alreadyUpdated);
	//const Gate* getGate1() const;
	//const Gate* getGate2() const;

};

#endif
