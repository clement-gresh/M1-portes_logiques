#include "LogicalGate.hpp"


// CONSTRUCTORS
// private
LogicalGate::LogicalGate(const LogicalGate& clone) : Gate{}, gates{ clone.getGates() } {
	std::cout << "Attention : construction d'une porte logique par COPIE (reference) !" << std::endl;
}

LogicalGate::LogicalGate(const LogicalGate* clone) : Gate{}, gates{ clone->getGates() } {
	std::cout << "Attention : construction d'une porte logique par COPIE (pointeur) !" << std::endl;
}

LogicalGate::LogicalGate() : Gate{}, gates{ std::vector<Gate*>{} } {
	std::cout << "Attention : construction d'une porte logique par defaut !" << std::endl;
}

// protected
LogicalGate::LogicalGate(const std::vector<Gate*> gates) : Gate{}, gates{ gates } {}

// METHODS
// Return the logical function corresponding to the gate
std::string const LogicalGate::logicalFunction(std::string const door) {
	std::string function = door + "(";
	int gateNumber = 0;

	for (const Gate* gate : this->getGates()) {
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