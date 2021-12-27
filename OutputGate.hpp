#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"
#include "LogicalGate.hpp"
#include "UpdateInterface.hpp"

class OutputGate : public IOGate, UpdateInterface {
private:
	static const std::regex format;
	static const char defaultName;
	LogicalGate* const logicalGate;


public:
	// CONSTRUCTORS
	OutputGate(const char name, LogicalGate* const gate);

	// METHODS
	virtual void updateGate();

	// ACCESSORS
	LogicalGate* const getLogicalGate() const;

};


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, OutputGate* const logicalGate);

#endif

