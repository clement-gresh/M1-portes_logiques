#ifndef NAND_GATE
#define NAND_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class NandGate : public LogicalGate {
private:
	// CONSTRUCTORS
	NandGate();

public:
	NandGate(Gate* const a, Gate* const b);
	NandGate(const NandGate& clone);
	NandGate(const NandGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif