#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"
#include "UpdateValueInterface.hpp"

class AndGate : public LogicalGate, UpdateValueInterface {
public:
	// CONSTRUCTORS
	AndGate(const Gate* a, const Gate *b);

	// METHODS
	void updateValue();
};

#endif