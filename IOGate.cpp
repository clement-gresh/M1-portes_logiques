#include "IOGate.hpp"

// CONSTRUCTEURS
IOGate::IOGate(const std::string nom) : Gate{}, nom { nom } {
	std::cout << "Construction d'une porte entree/sortie : " << nom << std::endl;
}


// ACCESSEURS
const std::string IOGate::getNom() const { return nom; }

void IOGate::setNom(const std::string nom) { this->nom = nom; }