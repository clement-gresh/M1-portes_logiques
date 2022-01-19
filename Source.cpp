#include "Circuit/Circuit.hpp"

#include <regex>

int main(int argc, char** argv)
{
	while (true) {
		Circuit* circuit;

		// Asking the user if they want to enter the logical expression of the circuit
		std::string s = "Do you want to write down the logical expression of the circuit - e.g.  A = or(a, and(b, c))  ?\n";
		s = s + "Otherwise the default circuit will be loaded. (y / n) ";
		std::string input = parser::userInput(s, std::regex{ "^[yn]$" });
		bool expressionIsCorrect = false;

		if (input.compare("y") == 0) {
			// Checking the syntax of the logical expression entered by the user
			while (!expressionIsCorrect) {
				std::cout << "Enter the logical expression of the circuit (type 'exit' to load the default circuit)." << std::endl;
				std::cout << "The gates that can be used are : ";
				for (std::string s : parser::gateNames) {
					std::cout << s << " ";
				}
				std::cout << std::endl;
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
			OrGate* orr = new OrGate(a, b);
			XorGate* and1 = new XorGate(c, d);
			NandGate* and2 = new NandGate(b, d);
			NotGate* and3 = new NotGate(a);
			NorGate* and4 = new NorGate(and1, and2);
			NxorGate* and5 = new NxorGate(orr, and3);
			AndGate* and6 = new AndGate(and4, and5);
			AndGate* and7 = new AndGate(and1, c);
			OutputGate* A = new OutputGate('A', and7);
			OutputGate* B = new OutputGate('d', and3);
			OutputGate* C = new OutputGate('C', and6);

			std::vector<InputGate*> inputGates = { a, b, c, d };
			std::vector<LogicalGate*> logicalGates = { orr, and1, and2, and3, and4, and5, and7, and6 };
			std::vector<OutputGate*> outputGates = { A, B, C };

			circuit = new Circuit(inputGates, logicalGates, outputGates);
		}

		try { circuit->simulateCircuit(); }
		catch (const std::invalid_argument& e) {
			std::cout << std::endl << "-----------------------------------------------------" << std::endl << std::endl;
			std::cout << "!!! Exception thrown !!!" << std::endl << e.what() << std::endl;
			std::cout << std::endl << "-----------------------------------------------------" << std::endl << std::endl;
		}


		// Asking the user if they want to simulate another circuit
		std::string s2 = "Do you want to simulate another circuit ? Otherwise the program will be terminated. (y / n) ";
		std::string exit = parser::userInput(s2, std::regex{ "^[yn]$" });
		if (exit.compare("n") == 0) { return 0; }
	}
	return 0;
}