#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"
#include "UpdateInterface.hpp"
#include "Drawing.hpp"

class AndGate : public LogicalGate {
private:
	// CONSTRUCTORS
	AndGate();

public:
	AndGate(Gate* const a, Gate* const b);
	AndGate(const AndGate& clone);
	AndGate(const AndGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif