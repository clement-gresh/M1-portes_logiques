#include "InputGate.hpp"
#include "AndGate.hpp"

#include <regex>


int main(int argc, char** argv)
{
	InputGate* testInput = new InputGate("a");
	InputGate* testInput2 = new InputGate("coucou");
	Gate* testInput3 = new InputGate("lol");
	/*
	InputGate testInput4 = *testInput; //copie
	InputGate& testInput5 = *testInput; //pas de copie
	InputGate* testInput6 = testInput; //pas de copie
	*/

	testInput->setValeur(true);
	testInput2->setValeur(true);
	testInput3->getValeur();

	AndGate* and1 = new AndGate(testInput, testInput2);
	std::cout <<  "La porte AND renvoie : " <<  and1->getValeur() << std::endl;

	return 0;
}