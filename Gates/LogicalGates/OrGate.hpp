#ifndef OR_GATE
#define OR_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class OrGate : public LogicalGate {
private:
	// CONSTRUCTORS
	OrGate();

public:
	OrGate(Gate* const a, Gate* const b);
	OrGate(const OrGate& clone);
	OrGate(const OrGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif