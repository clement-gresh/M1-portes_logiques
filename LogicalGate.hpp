#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Gate.hpp"

class LogicalGate : public Gate {
protected:
	const std::vector<Gate*> gates;
	//const Gate* gate1;
	//const Gate* gate2;

	// CONSTRUCTORS
	LogicalGate(const std::vector<Gate*> gates);
	//LogicalGate(const Gate* gate1, const Gate* gate2);


public:
	// ACCESSORS
	const std::vector<Gate*> getGates() const;
	//const Gate* getGate1() const;
	//const Gate* getGate2() const;

};

#endif
