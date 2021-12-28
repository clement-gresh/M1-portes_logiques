#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"
#include "Circuit.hpp"

#include <regex>


int main(int argc, char** argv)
{
	std::string test = "A   =  or ( a, and ( c ,d) )";


	// Creating the list of gate names that can be used in the expression
	std::vector<std::string> gateNames = { "and", "or" };


	// Creating the list of regex to check the expression
	std::vector< std::vector <std::regex> > regexList;

	regexList.push_back({ std::regex{ "^[A-Z](\\s)*" } });			// Output name
	regexList.push_back({ std::regex{ "^=(\\s)*" } });				// Equal sign

	std::vector <std::regex> temp;
	for (std::string gateName : gateNames) { temp.push_back(std::regex{ "^" + gateName + "(\\s)*" }); }		// Possible gate names
	regexList.push_back(temp);

	regexList.push_back({ std::regex{ "^\\( (\\s)*" } });			// Opening parenthesis
	regexList.push_back({ std::regex{ "(\\s)*\\)(\\s)*$" } });		// Closing parenthesis


	// Creating the list of error messages
	std::vector<std::string> expressionErrors;
	expressionErrors.push_back("Expression must start with the name of the output (a single capital letter).");
	expressionErrors.push_back("Expecting the sign equal '=' after the name of the output (a single capital letter).");

	std::string gateNameError{ "Expecting the name of a logical door after the sign equal : " };
	for (std::string gateName : gateNames) { gateNameError.append(gateName + " "); }
	expressionErrors.push_back(gateNameError);

	expressionErrors.push_back("Expecting an opening parenthesis '(' after the name of a logical gate.");
	expressionErrors.push_back("Expecting a closing parenthesis ')' at the end of the expression.");


	
	bool expressionIsCorrect = false;
	//while(!expressionIsIncorrect) { redo the whole thing (including asking the user if they want to write their own expression)

	// Checking the expression against each regex
	for (unsigned int i = 0; i < regexList.size(); i++) {
		expressionIsCorrect = false;

		for (std::regex regex2 : regexList.at(i)) {
			if (std::regex_search(test, regex2)) {
				test = std::regex_replace(test, regex2, "");
				expressionIsCorrect = true;
				break;
			}
		}

		if (!expressionIsCorrect) {
			std::cout << expressionErrors.at(i) << std::endl;
			break;
		}
	}


	std::cout << "test : '" << test << "'." << std::endl;

	/*
	std::regex outputRegex{ "^[A-Z](\\s)*" };
	std::regex equalRegex{ "^=(\\s)*" };
	std::regex gateRegex{ "^" + gates.at(0) + "(\\s)*"};
	std::regex openingParenthesisRegex{ "^\\( (\\s)*" };
	std::regex closingParenthesisRegex{ "(\\s)*\\)(\\s)* $" };
	

	if (std::regex_search(test, outputRegex)) {
		test = std::regex_replace(test, outputRegex, "");

		if (std::regex_search(test, equalRegex)) {
			test = std::regex_replace(test, equalRegex, "");

			if (std::regex_search(test, gateRegex)) {
				test = std::regex_replace(test, gateRegex, "");
				
				if (std::regex_search(test, openingParenthesisRegex)) {
					test = std::regex_replace(test, openingParenthesisRegex, "");


					if (std::regex_search(test, closingParenthesisRegex)) {
						test = std::regex_replace(test, closingParenthesisRegex, "");


					}
					else { std::cout << "Expecting a closing parenthesis ')' at the end of the expression." << std::endl; }

				}
				else { std::cout << "Expecting an opening parenthesis '(' after the name of a logical gate." << std::endl; }

			}
			else{ std::cout << "There must be at least one logical door after the sign equal." << std::endl; }
		}
		else { std::cout << "The name of the output must be followed by the sign equal '='." << std::endl; }
	}
	else { std::cout << "Expression must start with the name of the output (a single capital letter)." << std::endl; }
	*/


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
	AndGate* and5 = new AndGate(c, and3);
	OutputGate* A = new OutputGate('A', and2);
	OutputGate* B = new OutputGate('d', orr);
	OutputGate* C = new OutputGate('C', and3);
	OutputGate* D = new OutputGate('D', and4);
	OutputGate* E = new OutputGate('E', and5);

	std::vector<InputGate*> inputGates = { a, b, c, d };
	std::vector<LogicalGate*> logicalGates = { orr, and1, and3, and4, and5 };
	std::vector<OutputGate*> outputGates = { A, B, C, D, E };
	
	Circuit* circuit1 = new Circuit(inputGates, logicalGates, outputGates);

	circuit1->addLogicalGate(and2);

	circuit1->simulateCircuit();

	return 0;
}