#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"
#include "UpdateInterface.hpp"

class AndGate : public LogicalGate {
public:
	// CONSTRUCTORS
	AndGate(Gate* const a, Gate* const b);

	// METHODS
	virtual void updateGate();
};

#endif