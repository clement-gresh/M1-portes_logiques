#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"

class LogicalGate : public Gate {
protected:
	const std::vector<Gate*> gates;

	// CONSTRUCTORS
	LogicalGate(const std::vector<Gate*> gates);


public:
	// METHODS
	virtual void updateGate();
	std::string const logicalFunction(std::string const door);

	// ACCESSORS
	const std::vector<Gate*> getGates() const;

};

// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, LogicalGate* const gate);

#endif
