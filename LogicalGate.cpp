#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates } {}


void LogicalGate::updateGate() {
	// Updating the level of the gate in the drawing
	int max = 0;
	for (Gate* gate : this->getGates()) {
		if (gate->getGateLevel() > max)
			max = gate->getGateLevel();
	}
	this->setGateLevel(max + 1);
}

// Return the logical function corresponding to the gate
std::string const LogicalGate::logicalFunction(std::string const door) {
	std::string function = door + "(";
	int gateNumber = 0;

	for (Gate* gate : this->getGates()) {
		if (gateNumber == 0) { function.append(gate->getLogicalFunction()); }
		else { function.append(", ").append(gate->getLogicalFunction()); }
		gateNumber = gateNumber + 1;
	}
	function.append(")");
	return function;
}

// ACCESSORS
const std::vector<Gate*> LogicalGate::getGates() const { return this->gates; }


// Operator OVERLOAD
std::ostream& operator<<(std::ostream& out, LogicalGate* const gate) {
	out << "Logical function : " << gate->getLogicalFunction() << std::endl;
	out << "Value of Gate : " << gate->getValue() << std::endl << std::endl;
	return out;
};
