#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"
#include "LogicalGate.hpp"
#include "UpdateInterface.hpp"

class OutputGate : public IOGate, UpdateInterface {
private:
	static const std::regex format;
	static const char defaultName;
	Gate* const gate;


public:
	// CONSTRUCTORS
	OutputGate(const char name, Gate* const gate);

	// METHODS
	virtual void updateGate();

	// ACCESSORS
	Gate* const getGate() const;

};


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, OutputGate* const gate);

#endif

