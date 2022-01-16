#include "InputGate.hpp"

// Initialisation of static attributes
const std::regex InputGate::format{ "[a-z]" };
const char InputGate::defaultName{ 'z' };

// CONSTRUCTORS
InputGate::InputGate(const char name) :
	IOGate{ IOGate::checkNameFormating(name, InputGate::format, InputGate::defaultName) }
{
	this->alreadyUpdated = true;
	this->logicalFunction = std::string(1, this->name);
}

void InputGate::drawGate(Drawing& d){
	std::string val = this->value ? "1" : "0";
	std::string s{ std::string(1, this->name) + ":" + val + " " };
	d.draw(this->gateLine, this->gateColumn, s);
}
