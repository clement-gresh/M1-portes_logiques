#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"

#include <regex>


int main(int argc, char** argv)
{
	InputGate* testInput = new InputGate('a');
	InputGate* testInput2 = new InputGate('A');
	Gate* testInput3 = new InputGate('3');
	/*
	InputGate testInput4 = *testInput; //copie
	InputGate& testInput5 = *testInput; //pas de copie
	InputGate* testInput6 = testInput; //pas de copie
	*/

	testInput->setValue(true);
	testInput2->setValue(true);
	testInput3->getValue();

	AndGate* andTest = new AndGate(testInput, testInput2);
	std::cout <<  "La porte AND renvoie : " <<  andTest->getValue() << std::endl;
	std::cout << "Fin debug partie 1 "  << std::endl << std::endl;



	InputGate* a = new InputGate('a');
	InputGate* b = new InputGate('B');
	Gate* orr = new AndGate(a, b);
	Gate* and1 = new AndGate(a, b);
	Gate* and2 = new AndGate(orr , and1);
	OutputGate* A = new OutputGate('F', and2);
	OutputGate* B = new OutputGate('w', and1);



	return 0;
}