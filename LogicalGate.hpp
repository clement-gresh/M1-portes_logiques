#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"
#include "UpdateInterface.hpp"

class LogicalGate : public Gate, public UpdateInterface {
protected:
	const std::vector<Gate*> gates;

	// CONSTRUCTORS
	LogicalGate(const std::vector<Gate*> gates);


public:
	// METHODS
	std::string const logicalFunction(std::string const door);

	// ACCESSORS
	const std::vector<Gate*> getGates() const;

};

// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, LogicalGate* const gate);

#endif
