#include "Gate.hpp"

// CONSTRUCTEURS
Gate::Gate() : value{ false }, type{ GateType::DEFAULT } {}

Gate::Gate(const Gate& clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (reference) !" << std::endl;
}

Gate::Gate(const Gate* clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (pointeur) !" << std::endl;
}


// ACCESSEURS
const bool Gate::getValue() const { return value; }

const GateType Gate::getType() const {
	return this->type;
}

void Gate::setValue(const bool value) { this->value = value; }