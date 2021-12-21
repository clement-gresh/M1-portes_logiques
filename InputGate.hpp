#ifndef INPUT_GATE
#define INPUT_GATE

#include "IOGate.hpp"

class InputGate : public IOGate {
private:
	static const std::regex format;
	static const std::string defaultName;

public:
    // CONSTRUCTORS
    InputGate(const std::string name);

	// ACCESSORS
	// setValue() set to public for input gates
	using Gate::setValue;
};

#endif