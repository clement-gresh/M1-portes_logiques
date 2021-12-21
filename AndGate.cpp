#include "AndGate.hpp"

AndGate::AndGate(const Gate* a, const Gate* b) : Gate{} {
	if (a->getValue() && b->getValue()) this->value = true;
}
