#ifndef AND_GATE
#define AND_GATE

#include "Gate.hpp"

class AndGate : public Gate {
public:
	AndGate(const Gate* a, const Gate *b);
};

#endif

