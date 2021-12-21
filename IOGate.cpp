#include "IOGate.hpp"

// CONSTRUCTEURS
IOGate::IOGate(const std::string nom) : Gate{}, nom { nom } {
	std::cout << "Construction d'une porte entree/sortie : " << nom << std::endl; // debug
}


// METHODES
void IOGate::formaterNom(const std::string nom, const std::regex format, const std::string nomDefaut) {
	if (!std::regex_match(nom, format)) {
		this->nom = nomDefaut;
		std::cout << "Attention : le nom \"" << nom << "\" est invalide pour cette porte. Nom donne a la porte : " << nomDefaut << std::endl;
	}
}


// ACCESSEURS
const std::string IOGate::getNom() const { return nom; }

void IOGate::setNom(const std::string nom) { this->nom = nom; }