#ifndef CIRCUIT
#define CIRCUIT

#include "InputGate.hpp"
#include "LogicalGate.hpp"
#include "OutputGate.hpp"

#include <cmath>
#include <fstream>

class Circuit{
private:
	std::vector<InputGate*> inputGates;
	std::vector<LogicalGate*> logicalGates;
	std::vector<OutputGate*> outputGates;
    std::vector<std::vector<std::string>> circuitDrawing; // 2D array containing the drawing of the circuit
    std::vector<int> depthPerLevel; // Array containing on line 0 the maximum depth and on other lines the depth of each level 
    static const int LEVEL_HEIGHT;
    static const int GATE_WIDTH;


public:
    // CONSTRUCTORS
    Circuit(std::vector<InputGate*>& inputGates, std::vector<LogicalGate*> logicalGates, std::vector<OutputGate*> outputGates);

    // METHODS
    static const std::string userInput(const std::string message, const std::regex regex);
    void addLogicalGate(LogicalGate* const gate);
    // debugg : ajouter addInputGate, addOutputGate et les remove pour les 3;
    void buildCircuit(const std::string logicalFunction);
    void simulateCircuit();
    void updateCircuit(LogicalGate* const newGate);
    void updateCircuit(OutputGate* const newGate);
    void addLevel(const unsigned int gateLine);
    void addDepth(const int gateDepth);
    void addWire(Gate* const prevGate, Gate* const nextGate, const int gateNumber);
    void printCircuit();
    void saveFile();

    // ACCESSORS
    const std::vector<InputGate*>& getInputGates() const;
    const std::vector<LogicalGate*>& getLogicalGates() const;
    const std::vector<OutputGate*>& getOutputGates() const;
    const std::vector<std::vector<std::string>>& getCircuitDrawing() const;
    const std::vector<int>& getDepthPerLevel() const;
};


#endif