#ifndef CIRCUIT
#define CIRCUIT

#include "InputGate.hpp"
#include "LogicalGate.hpp"
#include "OutputGate.hpp"


class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;

};

#endif