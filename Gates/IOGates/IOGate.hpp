#ifndef IO_GATE
#define IO_GATE

#include "../Gate.hpp"

class IOGate : public Gate {
protected:
	const char name;

private:
	// CONSTRUCTORS
	IOGate(const IOGate& clone);
	IOGate(const IOGate* clone);
	IOGate();

protected:
	IOGate(const char name);

	// METHODS
	static char checkNameFormating(const char name, const std::regex format, const char defaultName);

public:
	// ACCESSEURS
	const char getName() const;
};

#endif