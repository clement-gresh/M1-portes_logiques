#ifndef CIRCUIT
#define CIRCUIT

#include "Parser.hpp"

#include <cmath>
#include <fstream>

class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;


public:
    // CONSTRUCTORS
    Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates);

    virtual ~Circuit();

    // METHODS
    void simulateCircuit();
    void saveFile();

    // ACCESSORS
    const std::vector<InputGate*>& getInputGates() const;
    const std::vector<LogicalGate*>& getLogicalGates() const;
    const std::vector<OutputGate*>& getOutputGates() const;
};


#endif