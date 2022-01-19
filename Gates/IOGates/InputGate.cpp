#include "InputGate.hpp"

// Initialisation of static attributes
const std::regex InputGate::format{ "[a-z]" };
const char InputGate::defaultName{ 'z' };

// CONSTRUCTORS
// private
InputGate::InputGate(const InputGate& clone) : IOGate{ clone.getName() } {}
InputGate::InputGate(const InputGate* clone) : IOGate{ clone->getName() } {}
InputGate::InputGate() : IOGate{ ' ' } {}

// public
InputGate::InputGate(const char name) :
	IOGate{ IOGate::checkNameFormating(name, InputGate::format, InputGate::defaultName) }
{
	this->alreadyUpdated = true;
	this->logicalFunction = std::string(1, this->name);
}

// METHODS
void InputGate::drawGate(Drawing& d){ this->draw(d, std::string(1, this->name), 0); }
