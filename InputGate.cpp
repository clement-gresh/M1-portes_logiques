#include "InputGate.hpp"

// Initialisation des attributs statiques
const std::regex InputGate::format{ "[a - z]" };
const std::string InputGate::nomDefaut{ "z" };

// CONSTRUCTEURS
InputGate::InputGate(const std::string nom) : IOGate{ nom } {
	this->formaterNom(nom, InputGate::format, InputGate::nomDefaut);
}