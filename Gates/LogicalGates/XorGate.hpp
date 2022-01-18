#ifndef XOR_GATE
#define XOR_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class XorGate : public LogicalGate {
private:
	// CONSTRUCTORS
	XorGate();

public:
	XorGate(Gate* const a, Gate* const b);
	XorGate(const XorGate& clone);
	XorGate(const XorGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif