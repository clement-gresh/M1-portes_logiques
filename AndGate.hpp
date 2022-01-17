#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"
#include "UpdateInterface.hpp"
#include "Drawing.hpp"

class AndGate : public LogicalGate {
public:
	// CONSTRUCTORS
	AndGate(Gate* const a, Gate* const b);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif