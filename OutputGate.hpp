#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"
#include "LogicalGate.hpp"
#include "UpdateValueInterface.hpp"

class OutputGate : public IOGate, UpdateValueInterface {
private:
	static const std::regex format;
	static const char defaultName;
	const LogicalGate* logicalGate;


public:
	// CONSTRUCTORS
	OutputGate(const char name, const LogicalGate* gate);

	// METHODS
	virtual void updateValue();

	// ACCESSORS
	const LogicalGate* getLogicalGate() const;

};

#endif

