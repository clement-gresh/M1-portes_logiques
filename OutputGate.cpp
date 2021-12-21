#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation des attributs statiques
const std::regex OutputGate::format{ "[A - Z]" };
const std::string OutputGate::defaultName{ "Z" };

// CONSTRUCTEURS
OutputGate::OutputGate(const std::string name) : IOGate{ name } {
	this->checkNameFormating(name, OutputGate::format, OutputGate::defaultName);
}
