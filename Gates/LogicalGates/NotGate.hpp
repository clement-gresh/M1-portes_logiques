#ifndef NOT_GATE
#define NOT_GATE

#include "LogicalGate.hpp"
#include "../UpdateInterface.hpp"
#include "../../Circuit/Circuit.hpp"

class NotGate : public LogicalGate {
private:
	// CONSTRUCTORS
	NotGate();

public:
	NotGate(Gate* const a);
	NotGate(const NotGate& clone);
	NotGate(const NotGate* clone);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);
};

#endif