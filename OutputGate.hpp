#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"

class OutputGate : public IOGate {
private:
	static const std::regex format;
	static const char defaultName;

public:
	// CONSTRUCTORS
	OutputGate(const char name, const Gate* gate);
};

#endif

