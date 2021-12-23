#ifndef CIRCUIT
#define CIRCUIT

#include "InputGate.hpp"
#include "LogicalGate.hpp"
#include "OutputGate.hpp"


class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;
    //std::vector<Gate*> circuitGates; // Debug : ajouter accessors ?  // debug : option 1


public:
    // CONSTRUCTORS
    Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates);

    // METHODS
    void addLogicalGate(LogicalGate* const logicalGate);
    // debugg : ajouter addInputGate, addOutputGate et les remove pour les 3;
    //void addCircuitGate(Gate* const gate);  // debug : option 1
    //void nextGate(LogicalGate* const gate); // debug : option 1
    void simulateCircuit();

    // ACCESSORS
    const std::vector<InputGate*>& getInputGates() const;
    const std::vector<LogicalGate*>& getLogicalGates() const;
    const std::vector<OutputGate*>& getOutputGates() const;
    //const std::vector<Gate*>& getCircuitGates() const;  // debug : option 1
};

#endif