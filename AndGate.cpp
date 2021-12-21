#include "AndGate.hpp"

AndGate::AndGate(const Gate* a, const Gate* b) : Gate{} {
	if (a->getValeur() && b->getValeur()) this->valeur = true;
}
