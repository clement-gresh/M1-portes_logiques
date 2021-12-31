#ifndef IO_GATE
#define IO_GATE

#include "Gate.hpp"

class IOGate : public Gate {
protected:
	const char name;

	// CONSTRUCTEURS
	IOGate(const GateType type, const char name);

	// METHODES
	static char checkNameFormating(const char name, const std::regex format, const char defaultName);

public:
	// ACCESSEURS
	const char getName() const;
};

#endif