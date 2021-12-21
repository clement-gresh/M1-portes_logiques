#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation des attributs statiques
const std::regex OutputGate::format{ "[A - Z]" };
const std::string OutputGate::nomDefaut{ "Z" };

// CONSTRUCTEURS
OutputGate::OutputGate(const std::string nom) : IOGate{ nom } {
	this->formaterNom(nom, OutputGate::format, OutputGate::nomDefaut);
}
