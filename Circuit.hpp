#ifndef CIRCUIT
#define CIRCUIT

#include "InputGate.hpp"
#include "LogicalGate.hpp"
#include "OutputGate.hpp"

#include <cmath>

class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;
    std::vector<std::vector<std::string>> circuitDrawing;
    static const int LEVEL_HEIGHT;
    static const int GATE_WIDTH;


public:
    // CONSTRUCTORS
    Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates);

    // METHODS
    void addLogicalGate(LogicalGate* const logicalGate);
    // debugg : ajouter addInputGate, addOutputGate et les remove pour les 3;
    void simulateCircuit();
    void addWire(Gate* const prevGate, Gate* const nextGate, const int gateNumber);
    void printCircuit();

    // ACCESSORS
    const std::vector<InputGate*>& getInputGates() const;
    const std::vector<LogicalGate*>& getLogicalGates() const;
    const std::vector<OutputGate*>& getOutputGates() const;
    const std::vector<std::vector<std::string>>& getCircuitDrawing() const;
};

#endif