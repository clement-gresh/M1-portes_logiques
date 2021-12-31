#include "InputGate.hpp"

// Initialisation of static attributes
const std::regex InputGate::format{ "[a-z]" };
const char InputGate::defaultName{ 'z' };

// CONSTRUCTORS
InputGate::InputGate(const char name) :
	IOGate{ GateType::INPUT, IOGate::checkNameFormating(name, InputGate::format, InputGate::defaultName) }
{
	this->alreadyUpdated = true;
	this->logicalFunction = std::string(1, this->name);
}