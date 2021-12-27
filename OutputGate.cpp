#include "OutputGate.hpp"
#include "OutputGate.hpp"

// Initialisation of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };

// CONSTRUCTORS
OutputGate::OutputGate(const char name, LogicalGate* const gate) : IOGate{ name }, logicalGate{ gate } {
	this->type = GateType::OUTPUT;
	this->checkNameFormating(name, OutputGate::format, OutputGate::defaultName);
}

void OutputGate::updateGate() {
	// Same value, logical function and depth as its input
	this->setValue( this->getLogicalGate()->getValue() );
	this->setGateDepth(this->getLogicalGate()->getGateDepth());

	// Add the output name and = to the logical function
	std::string function = std::string(1, this->getName()) + "=" + this->getLogicalGate()->getLogicalFunction();
	this->setLogicalFunction(function);

	// One level above its input
	this->setGateLevel(this->getLogicalGate()->getGateLevel() + 1);
}

LogicalGate* const OutputGate::getLogicalGate() const { return this->logicalGate; }



// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, OutputGate* const OutputGate) {
	out << "The value of the Output Gate \"" << OutputGate->getName() << "\"  is : " << OutputGate->getValue() << std::endl;
	out << "Logical function : " << OutputGate->getLogicalFunction() << std::endl << std::endl;
	return out;
}