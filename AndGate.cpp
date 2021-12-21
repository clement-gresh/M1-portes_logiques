#include "AndGate.hpp"

const bool AndGate::logicalOperation(const bool input1, const bool input2) {
	std::cout << "logicalOperation of AndGate" << std::endl;
	return (input1 && input2);
}

AndGate::AndGate(const Gate* a, const Gate* b) : LogicalGate{a, b, &logicalOperation} {}











//const Gate* gate1, const Gate* gate2, const bool (AndGate::*function)(const bool, const bool)