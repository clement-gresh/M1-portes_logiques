#include "InputGate.hpp"

// Initialisation of static attributes
const std::regex InputGate::format{ "[a-z]" };
const char InputGate::defaultName{ 'z' };

// CONSTRUCTORS
// private
InputGate::InputGate(const InputGate& clone) : IOGate{ clone.getName() } {
	std::cout << "Attention : construction d'une porte d'entree par COPIE (reference) !" << std::endl;
}

InputGate::InputGate(const InputGate* clone) : IOGate{ clone->getName() } {
	std::cout << "Attention : construction d'une porte d'entree par COPIE (pointeur) !" << std::endl;
}

InputGate::InputGate() : IOGate{ ' ' } {
	std::cout << "Attention : construction d'une porte d'entree par defaut !" << std::endl;
}

// public
InputGate::InputGate(const char name) :
	IOGate{ IOGate::checkNameFormating(name, InputGate::format, InputGate::defaultName) }
{
	this->alreadyUpdated = true;
	this->logicalFunction = std::string(1, this->name);
}

// METHODS
void InputGate::drawGate(Drawing& d){ this->draw(d, std::string(1, this->name), 0); }
