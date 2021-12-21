#include "InputGate.hpp"

// Initialisation des attributs statiques
const std::regex InputGate::format{ "[a - z]" };
const std::string InputGate::defaultName{ "z" };

// CONSTRUCTEURS
InputGate::InputGate(const std::string name) : IOGate{ name } {
	this->checkNameFormating(name, InputGate::format, InputGate::defaultName);
}