#ifndef GATE
#define GATE

#include "GateType.hpp"

#include <string>
#include <regex>


class Gate {
protected:
	bool value;
	GateType type;

	// CONSTRUCTORS
	Gate();
	Gate(const Gate& clone);
	Gate(const Gate* clone);

	// ACCESSORS
	void setValue(const bool value);

public:
	const bool getValue() const;
	const GateType getType() const;
};


#endif