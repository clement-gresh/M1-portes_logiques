#ifndef INPUT_GATE
#define INPUT_GATE

#include "IOGate.hpp"
#include "Drawing.hpp"

class InputGate : public IOGate {
private:
	static const std::regex format;
	static const char defaultName;

public:
    // CONSTRUCTORS
    InputGate(const char name);

	// METHODS
	virtual void drawGate(Drawing& d);

	// ACCESSORS
	// setting setValue() to public for input gates
	using Gate::setValue;
};

#endif