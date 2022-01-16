#include "OutputGate.hpp"
#include "OutputGate.hpp"

// INITIALISATION of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };


// CONSTRUCTORS
OutputGate::OutputGate(const char name, Gate* const gate) :
	IOGate{ IOGate::checkNameFormating(name, OutputGate::format, OutputGate::defaultName) },
	gate{ gate } {}

void OutputGate::updateGate() {
	// Same value its input
	this->setValue( this->getGate()->getValue() );
	
	// Same depth as its input (or at least 1)
	this->setGateColumn( std::max(this->getGate()->getGateColumn(), 1) );

	// One level above its input
	int max = 0;
	if (gate->getGateLine() > max) { max = gate->getGateLine(); }
	this->setGateLine(max + 1);

	// Add the output name and the sign equal '=' to the logical function of the input
	std::string function = std::string(1, this->getName()) + " = " + this->getGate()->getLogicalFunction();
	this->setLogicalFunction(function);
}

Gate* const OutputGate::getGate() const { return this->gate; }


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, OutputGate* const OutputGate) {
	out << "The value of the Output Gate \"" << OutputGate->getName() << "\"  is : " << OutputGate->getValue() << std::endl;
	out << "Logical function : " << OutputGate->getLogicalFunction() << std::endl << std::endl;
	return out;
}