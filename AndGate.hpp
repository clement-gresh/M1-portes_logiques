#ifndef AND_GATE
#define AND_GATE

#include "LogicalGate.hpp"

class AndGate : public LogicalGate {
private:
	static const bool logicalOperation(const bool input1, const bool input2);

public:
	AndGate(const Gate* a, const Gate *b);
};

#endif