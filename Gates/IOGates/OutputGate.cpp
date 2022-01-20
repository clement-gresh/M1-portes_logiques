#include "OutputGate.hpp"
#include "OutputGate.hpp"

// INITIALISATION of static attributes
const std::regex OutputGate::format{ "[A-Z]" };
const char OutputGate::defaultName{ 'Z' };


// CONSTRUCTORS
// private
OutputGate::OutputGate(const OutputGate& clone) : IOGate{ clone.getName() }, gate{ clone.getGate() } {}
OutputGate::OutputGate(const OutputGate* clone) : IOGate{ clone->getName() }, gate{ clone->getGate() } {}
OutputGate::OutputGate() : IOGate{ ' ' }, gate{ nullptr } {}

// public
OutputGate::OutputGate(const char name, Gate* const gate) :
	IOGate{ IOGate::checkNameFormating(name, OutputGate::format, OutputGate::defaultName) },
	gate{ gate } {}

// METHODS
void OutputGate::updateGate() {
	// Same value as its input
	this->setValue( this->getGate()->getValue() );
	
	// Same column as its input (or at least 4)
	this->setGateColumn( std::max(static_cast<int>(this->getGate()->getGateColumn()), 4) );

	// One level above its input
	unsigned int max = 0;
	if (gate->getGateLine() > max) { max = gate->getGateLine(); }
	this->setGateLine(max + 1);

	// Add the output name and the sign equal '=' to the logical function of the input
	std::string function = std::string(1, this->getName()) + " = " + this->getGate()->getLogicalFunction();
	this->setLogicalFunction(function);
}

void OutputGate::drawGate(Drawing& d) { this->draw(d, std::string(1, this->name), 0); }

// ACCESSORS
Gate* const OutputGate::getGate() const { return this->gate; }


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, const OutputGate* OutputGate) {
	out << "The value of the Output Gate \"" << OutputGate->getName() << "\"  is : " << OutputGate->getValue() << std::endl;
	out << "Logical function : " << OutputGate->getLogicalFunction() << std::endl << std::endl;
	return out;
}
