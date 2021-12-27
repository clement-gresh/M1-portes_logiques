#include "LogicalGate.hpp"


// CONSTRUCTORS
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates } {}


void LogicalGate::updateGate() {
	// Updating the level of the gate in the drawing
	int max = 0;
	for (Gate* gate : this->getGates()) {
		if (gate->getGateLevel() > max && gate->getType() != GateType::INPUT)
			max = gate->getGateLevel();
	}
	this->setGateLevel(max + 1);


	// Updating the logical function corresponding to this gate
	std::string function = "";
	function = (this->getType() * function) + "(";
	int gateNumber = 0;

	for (Gate* gate : this->getGates()) {
		//if (gateNumber == 0) { function = function + gate->getLogicalFunction(); }
		//else { function = function + "," + gate->getLogicalFunction(); }

		if (gateNumber == 0) { function.append(gate->getLogicalFunction()); }
		else { function.append(",").append(gate->getLogicalFunction()); }
		
		gateNumber = gateNumber + 1;
	}
	function.append(")");
	//function = function + ")";

	this->setLogicalFunction(function);
}

// ACCESSORS
const std::vector<Gate*> LogicalGate::getGates() const { return this->gates; }


// Operator OVERLOAD
std::ostream& operator<<(std::ostream& out, LogicalGate* const logicalGate) {
	out << "Value of Gate \"" << logicalGate->getType() << "\" : " << logicalGate->getValue() << std::endl;
	out << "Logical function : " << logicalGate->getLogicalFunction() << std::endl << std::endl;
	return out;
};
