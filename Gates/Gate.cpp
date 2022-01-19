#include "Gate.hpp"

// CONSTRUCTEURS
// private
Gate::Gate(const Gate& clone) : Gate{} {}
Gate::Gate(const Gate* clone) : Gate{} {}

// protected
Gate::Gate() : value{ false }, alreadyUpdated{ false }, gateLine{ 0 }, gateColumn{ 0 }, logicalFunction{ "" } {}



// ACCESSEURS
// protected
void Gate::setValue(const bool value) { this->value = value; }
void Gate::setLogicalFunction(const std::string function) { this->logicalFunction = function; }

void Gate::draw(Drawing& d, const std::string s, const int offset){
	int size = s.size();
	for (int i = 0; i < size; i++) {
		d.draw(this->gateLine, this->gateColumn - offset + i, s.substr(i,1));
	}
	d.draw(this->gateLine, this->gateColumn - offset + size, ":");
	d.draw(this->gateLine, this->gateColumn - offset + size + 1, this->value ? "1" : "0");
}

// public
const bool Gate::getValue() const { return value; }
const bool Gate::getAlreadyUpdated() const { return this->alreadyUpdated; }
const unsigned int Gate::getGateLine() const { return this->gateLine; }
const unsigned int Gate::getGateColumn() const { return this->gateColumn; }
const std::string Gate::getLogicalFunction() const { return this->logicalFunction; }

void Gate::setAlreadyUpdated(const bool alreadyUpdated) { this->alreadyUpdated = alreadyUpdated; }
void Gate::setGateLine(const int level) { this->gateLine = level; }
void Gate::setGateColumn(const int depth) { this->gateColumn = depth; }
