#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };

// CONSTRUCTORS
OutputGate::OutputGate(const char name, const Gate* gate) : IOGate{ name } {
	this->checkNameFormating(name, OutputGate::format, OutputGate::defaultName);

	this->value = gate->getValue();
}
