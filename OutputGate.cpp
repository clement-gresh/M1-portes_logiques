#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };

// CONSTRUCTORS
OutputGate::OutputGate(const char name, LogicalGate* const gate) : IOGate{ name }, logicalGate{ gate } {
	this->type = GateType::OUTPUT;
	this->checkNameFormating(name, OutputGate::format, OutputGate::defaultName);
}

void OutputGate::updateGate() {
	this->setValue( this->getLogicalGate()->getValue() );
	this->setLogicalFunction ( this->getLogicalGate()->getLogicalFunction() );
}

LogicalGate* const OutputGate::getLogicalGate() const { return this->logicalGate; }
