#include "Gate.hpp"

// CONSTRUCTEURS
Gate::Gate() : value{ false }, type{ GateType::DEFAULT }, alreadyUpdated{ false }, gateLevel{ 0 }, gateDepth{ 0 } {}

Gate::Gate(const Gate& clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (reference) !" << std::endl;
}

Gate::Gate(const Gate* clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (pointeur) !" << std::endl;
}


// ACCESSEURS
// private
void Gate::setValue(const bool value) { this->value = value; }

// public
const bool Gate::getValue() const { return value; }
const GateType Gate::getType() const { return this->type; }
const bool Gate::getAlreadyUpdated() const { return this->alreadyUpdated; }
const int Gate::getGateLevel() const { return this->gateLevel; }
const int Gate::getGateDepth() const { return this->gateDepth; }

void Gate::setAlreadyUpdated(const bool alreadyUpdated) { this->alreadyUpdated = alreadyUpdated; }
void Gate::setGateLevel(const int level) { this->gateLevel = level; }
void Gate::setGateDepth(const int depth) { this->gateDepth = depth; }