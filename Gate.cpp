#include "Gate.hpp"

// CONSTRUCTEURS
Gate::Gate() : valeur{ false } {
	std::cout << "Construction d'une porte." << std::endl;
}

Gate::Gate(const Gate& clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (reference) !" << std::endl;
}

Gate::Gate(const Gate* clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (pointeur) !" << std::endl;
}



// ACCESSEURS
const bool Gate::getValeur() const { return valeur; }

void Gate::setValeur(const bool valeur) { this->valeur = valeur; }