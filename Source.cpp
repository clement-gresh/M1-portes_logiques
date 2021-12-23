#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"
#include "Circuit.hpp"

#include <regex>


int main(int argc, char** argv)
{
	/* debug
	InputGate* testInput = new InputGate('a');
	InputGate* testInput2 = new InputGate('A');
	
	InputGate testInput4 = *testInput; //copie
	InputGate& testInput5 = *testInput; //pas de copie
	InputGate* testInput6 = testInput; //pas de copie
	

	testInput->setValue(true);
	testInput2->setValue(true);

	Gate* andTest = new AndGate(testInput, testInput2);
	std::cout <<  "La porte AND renvoie : " <<  andTest->getValue() << std::endl << std::endl;
	*/


	InputGate* a = new InputGate('a');
	InputGate* b = new InputGate('w');
	AndGate* orr = new AndGate(a, a);
	AndGate* and1 = new AndGate(a, b);
	AndGate* and2 = new AndGate(orr , and1);
	OutputGate* A = new OutputGate('F', and2);
	OutputGate* B = new OutputGate('W', orr);

	std::vector<InputGate*> inputGates = { a, b };
	std::vector<LogicalGate*> logicalGates = { orr, and1 };
	std::vector<OutputGate*> outputGates = { A, B };
	
	Circuit* circuit1 = new Circuit(inputGates, logicalGates, outputGates);

	circuit1->addLogicalGate(and2);

	circuit1->simulateCircuit();

	return 0;
}