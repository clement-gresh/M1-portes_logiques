#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"
#include "LogicalGate.hpp"
#include "UpdateValueInterface.hpp"

class OutputGate : public IOGate, UpdateValueInterface {
private:
	static const std::regex format;
	static const char defaultName;
	LogicalGate* const logicalGate;


public:
	// CONSTRUCTORS
	OutputGate(const char name, LogicalGate* const gate);

	// METHODS
	virtual void updateValue();

	// ACCESSORS
	LogicalGate* const getLogicalGate() const;

};

#endif

