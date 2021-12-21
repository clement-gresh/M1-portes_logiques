#include "LogicalGate.hpp"


LogicalGate::LogicalGate(const Gate* gate1, const Gate* gate2, const bool (*function)(const bool, const bool)) {
	if( function(gate1->getValue(), gate2->getValue()) )  this->value = true;
}

/*
LogicalGate::LogicalGate(const Gate* gate1, const Gate* gate2) : Gate{} {
	if (logicalOperation( gate1->getValue(), gate2->getValue() )) this->value = true;
}


bool LogicalGate::logicalOperation(const bool input1, const bool input2) {
	std::cout << "logicalOperation of LogicalGate" << std::endl;
	return false;
}
*/