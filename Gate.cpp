#include "Gate.hpp"

// CONSTRUCTEURS
Gate::Gate() : value{ false }, alreadyUpdated{ false }, gateLine{ 0 }, gateColumn{ 0 }, logicalFunction{ "" } {}

Gate::Gate(const Gate& clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (reference) !" << std::endl;
}

Gate::Gate(const Gate* clone) : Gate{} {
	std::cout << "Attention : construction d'une porte par COPIE (pointeur) !" << std::endl;
}


// ACCESSEURS
// private
void Gate::setValue(const bool value) { this->value = value; }
void Gate::setLogicalFunction(const std::string function) { this->logicalFunction = function; }

// public
const bool Gate::getValue() const { return value; }
const bool Gate::getAlreadyUpdated() const { return this->alreadyUpdated; }
const int Gate::getGateLine() const { return this->gateLine; }
const int Gate::getGateColumn() const { return this->gateColumn; }
const std::string Gate::getLogicalFunction() const { return this->logicalFunction; }

void Gate::setAlreadyUpdated(const bool alreadyUpdated) { this->alreadyUpdated = alreadyUpdated; }
void Gate::setGateLine(const int level) { this->gateLine = level; }
void Gate::setGateColumn(const int depth) { this->gateColumn = depth; }