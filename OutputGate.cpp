#include "OutputGate.hpp"
#include "OutputGate.hpp"

// INITIALISATION of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };


// CONSTRUCTORS
OutputGate::OutputGate(const char name, LogicalGate* const gate) : 
	IOGate{ GateType::OUTPUT, checkNameFormating(name, OutputGate::format, OutputGate::defaultName) },
	logicalGate{ gate } {}

void OutputGate::updateGate() {
	// Same value and depth as its input
	this->setValue( this->getLogicalGate()->getValue() );
	this->setGateDepth(this->getLogicalGate()->getGateDepth());

	// One level above its input
	this->setGateLevel(this->getLogicalGate()->getGateLevel() + 1);

	// Add the output name and the sign equal '=' to the logical function of the input
	std::string function = std::string(1, this->getName()) + "=" + this->getLogicalGate()->getLogicalFunction();
	this->setLogicalFunction(function);
}

LogicalGate* const OutputGate::getLogicalGate() const { return this->logicalGate; }


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, OutputGate* const OutputGate) {
	out << "The value of the Output Gate \"" << OutputGate->getName() << "\"  is : " << OutputGate->getValue() << std::endl;
	out << "Logical function : " << OutputGate->getLogicalFunction() << std::endl << std::endl;
	return out;
}