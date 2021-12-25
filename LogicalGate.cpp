#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates } {}


void LogicalGate::updateLevel() {
	// Updating the level (line)
	int max = 0;
	for (Gate* gate : this->getGates()) {
		if (gate->getGateLevel() > max && gate->getType() != GateType::INPUT)
			max = gate->getGateLevel();
	}
	this->setGateLevel(max + 1);
}

// ACCESSORS
const std::vector<Gate*> LogicalGate::getGates() const { return this->gates; }
