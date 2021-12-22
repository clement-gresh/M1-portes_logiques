#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };

// CONSTRUCTORS
OutputGate::OutputGate(const char name, const LogicalGate* gate) : IOGate{ name }, logicalGate{ gate } {
	this->checkNameFormating(name, OutputGate::format, OutputGate::defaultName);
}

void OutputGate::updateValue() {
	this->value = this->getLogicalGate()->getValue();
}

const LogicalGate* OutputGate::getLogicalGate() const { return logicalGate; }
