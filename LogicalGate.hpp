#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"

class LogicalGate : public Gate {
protected:
	const std::vector<Gate*> gates;

	// CONSTRUCTORS
	LogicalGate(const std::vector<Gate*> gates);


public:
	// METHODS
	virtual void updateValue() {};
	void updateLevel();

	// ACCESSORS
	const std::vector<Gate*> getGates() const;

};

#endif
