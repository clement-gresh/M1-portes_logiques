#include "InputGate.hpp"

// Initialisation of static attributes
const std::regex InputGate::format{ "[a-z]" };
const char InputGate::defaultName{ 'z' };

// CONSTRUCTORS
InputGate::InputGate(const char name) : IOGate{ name } {
	this->checkNameFormating(name, InputGate::format, InputGate::defaultName);
}