#ifndef CIRCUIT
#define CIRCUIT

#include "Parser.hpp"
#include "Drawing.hpp"

#include <cmath>
#include <fstream>

class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;
    Drawing drawing;


public:
    // CONSTRUCTORS
    Circuit(const std::vector<InputGate*>& inputGates, const std::vector<LogicalGate*>& logicalGates,
            const std::vector<OutputGate*>& outputGates);

    // DESTRUCTOR
    virtual ~Circuit();

    // METHODS
    void simulateCircuit();
    void saveFile();

    // ACCESSORS
    const std::vector<InputGate*>& getInputGates() const;
    const std::vector<LogicalGate*>& getLogicalGates() const;
    const std::vector<OutputGate*>& getOutputGates() const;
    const Drawing& getDrawing() const;
};


#endif