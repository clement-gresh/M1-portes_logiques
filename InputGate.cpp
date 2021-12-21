#include "InputGate.hpp"


// CONSTRUCTEURS
InputGate::InputGate(const std::string nom) : IOGate{ nom } {
	
	if (!std::regex_match(nom, std::regex("[a - z]"))) {
		this->nom = "z";
		std::cout << "Attention : le nom \"" << nom << "\" est invalide pour une porte d'entree. Nom donne a la porte : \"z\"." << std::endl;
	}
}