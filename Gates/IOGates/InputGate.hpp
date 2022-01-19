#ifndef INPUT_GATE
#define INPUT_GATE

#include "IOGate.hpp"
#include "../../Circuit/Drawing.hpp"

class InputGate final : public IOGate {
private:
	static const std::regex format;
	static const char defaultName;

	// CONSTRUCTORS
	InputGate(const InputGate& clone);
	InputGate(const InputGate* clone);
	InputGate();

public:
    InputGate(const char name);

	// METHODS
	virtual void drawGate(Drawing& d);

	// ACCESSORS
	// setting setValue() to public for input gates
	using Gate::setValue;
};

#endif
