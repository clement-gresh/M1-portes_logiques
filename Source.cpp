#include "Circuit.hpp"

#include <regex>

int main(int argc, char** argv)
{
	Circuit* circuit;

	// Asking the user if they want to enter the logical expression of the circuit
	std::string s = "Do you want to write down the logical expression of the circuit - e.g.  A = or(a, and(b, c))  ?\n";
	s = s + "Otherwise the default circuit will be loaded. (y / n) ";
	std::string input = parser::userInput(s, std::regex{ "^[yn]$" });
	bool expressionIsCorrect = false;

	if (input.compare("y") == 0) {
		// Checking the syntax of the logical expression entered by the user
		while (!expressionIsCorrect) {
			std::cout << "Enter the logical expression of the circuit (type 'exit' to load the default circuit) : ";
			std::getline(std::cin, input);

			if (input.compare("exit") == 0) { break; }
		
			expressionIsCorrect = parser::checkLogicalFunction(input);
			std::cout << std::endl;
		}
	}

	// Creating a circuit from the logical expression
	if (expressionIsCorrect) {
		std::cout << "The syntax of the expression is correct, now creating the circuit." << std::endl;
		circuit = parser::createCircuit(input);
	}

	// Creating a circuit by creating gates
	else {
		std::cout << std::endl << "Loading pre-existing circuit." << std::endl;

		InputGate* a = new InputGate('a');
		InputGate* b = new InputGate('w');
		InputGate* c = new InputGate('c');
		InputGate* d = new InputGate('F');
		AndGate* orr = new AndGate(a, b);
		AndGate* and1 = new AndGate(c, d);
		AndGate* and2 = new AndGate(b, d);
		AndGate* and3 = new AndGate(a, a);
		AndGate* and4 = new AndGate(and1, and3);
		AndGate* and5 = new AndGate(orr, and2);
		AndGate* and6 = new AndGate(and4, and5);
		OutputGate* A = new OutputGate('A', orr);
		OutputGate* B = new OutputGate('d', and3);
		OutputGate* C = new OutputGate('C', and6);

		std::vector<InputGate*> inputGates = { a, b, c, d };
		std::vector<LogicalGate*> logicalGates = { orr, and1, and2, and3, and4, and5, and6 };
		std::vector<OutputGate*> outputGates = { A, B, C };

		circuit = new Circuit(inputGates, logicalGates, outputGates);
	}

	circuit->simulateCircuit();

	return 0;
}