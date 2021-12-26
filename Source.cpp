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
	InputGate* c = new InputGate('c');
	InputGate* d = new InputGate('F');
	AndGate* orr = new AndGate(a, a);
	AndGate* and1 = new AndGate(a, b);
	AndGate* and2 = new AndGate(orr , and1);
	AndGate* and3 = new AndGate(a, c);
	AndGate* and4 = new AndGate(and3, and1);
	OutputGate* A = new OutputGate('A', and2);
	OutputGate* B = new OutputGate('d', orr);
	OutputGate* C = new OutputGate('C', and3);
	OutputGate* D = new OutputGate('D', and4);

	std::vector<InputGate*> inputGates = { a, b, c, d };
	std::vector<LogicalGate*> logicalGates = { orr, and1, and3, and4 };
	std::vector<OutputGate*> outputGates = { A, B, C, D };
	
	Circuit* circuit1 = new Circuit(inputGates, logicalGates, outputGates);

	circuit1->addLogicalGate(and2);

	circuit1->simulateCircuit();

	return 0;
}