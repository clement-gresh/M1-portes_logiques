#ifndef INPUT_GATE
#define INPUT_GATE

#include "IOGate.hpp"

class InputGate : public IOGate {
private:
	static const std::regex format;
	static const char defaultName;
	const std::string coucou; //debug

public:
    // CONSTRUCTORS
    InputGate(const char name);

	// ACCESSORS
	// setValue() set to public for input gates
	using Gate::setValue;
};

#endif