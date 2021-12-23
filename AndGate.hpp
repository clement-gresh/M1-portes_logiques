#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"
#include "UpdateValueInterface.hpp"

class AndGate : public LogicalGate, UpdateValueInterface {
public:
	// CONSTRUCTORS
	AndGate(Gate* const a, Gate* const b);


	// METHODS
	void updateValue();
};

#endif