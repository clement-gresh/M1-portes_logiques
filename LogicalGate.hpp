#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"

class LogicalGate : public Gate {
protected:
	LogicalGate(const Gate* gate1, const Gate* gate2, const bool (*function)(const bool, const bool));
};

#endif
