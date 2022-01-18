#ifndef NOR_GATE
#define NOR_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class NorGate : public LogicalGate {
private:
	// CONSTRUCTORS
	NorGate();

public:
	NorGate(Gate* const a, Gate* const b);
	NorGate(const NorGate& clone);
	NorGate(const NorGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif