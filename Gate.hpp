#ifndef GATE
#define GATE

#include <string>
#include <iostream>
#include <regex>

class Gate {
protected:
	bool value;

	// CONSTRUCTORS
	Gate();
	Gate(const Gate& clone);
	Gate(const Gate* clone);

	// ACCESSORS
	void setValue(const bool value);

public:
	const bool getValue() const;
};


#endif