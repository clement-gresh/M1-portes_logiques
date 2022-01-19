#include "Circuit/Circuit.hpp"

#include <regex>

int main(int argc, char** argv)
{
	while (true) {
	
		std::cout << std::endl << std::endl << "-----------------------------------START-----------------------------------" << std::endl << std::endl;
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
			OrGate* or1 = new OrGate(a, b);
			XorGate* xor1 = new XorGate(c, d);
			NandGate* nand1 = new NandGate(b, d);
			NotGate* not1 = new NotGate(a);
			NorGate* nor1 = new NorGate(xor1, nand1);
			NxorGate* nxor1 = new NxorGate(or1, not1);
			AndGate* and2 = new AndGate(nor1, nxor1);
			XorGate* xor2 = new XorGate(xor1, c);
			OutputGate* A = new OutputGate('A', xor2);
			OutputGate* B = new OutputGate('d', not1);
			OutputGate* C = new OutputGate('C', and2);

			std::vector<InputGate*> inputGates = { a, b, c, d };
			std::vector<LogicalGate*> logicalGates = { or1, xor1, nand1, not1, nor1, nxor1, xor2, and2 };
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
