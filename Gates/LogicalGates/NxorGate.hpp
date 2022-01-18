#ifndef NXOR_GATE
#define NXOR_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class NxorGate : public LogicalGate {
private:
	// CONSTRUCTORS
	NxorGate();

public:
	NxorGate(Gate* const a, Gate* const b);
	NxorGate(const NxorGate& clone);
	NxorGate(const NxorGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif