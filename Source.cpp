#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"
#include "Circuit.hpp"

#include <regex>



const int OUTPUT_NAME = 0;
const int EQUAL_SIGN = 1;
const int GATE_NAME = 2;
const int OPENING_PARENTHESIS = 3;
const int CLOSING_PARENTHESIS = 4;
const int INPUT_NAME = 5;

bool checkGateExpression(std::string expression, const std::vector< std::vector <std::regex> > regexList,
	const std::vector<std::string> expressionErrors);


int main(int argc, char** argv)
{
	std::string expression = "A   =  or( a, and ( and(c, e) ,d) )";


	// Creating the list of gate names that can be used in the expression
	std::vector<std::string> gateNames = { "and", "or" };


	// Creating the list of regex to check the expression
	std::vector< std::vector <std::regex> > regexList;

	regexList.push_back({ std::regex{ "^[A-Z](\\s)*" } });			// Output name
	regexList.push_back({ std::regex{ "^=(\\s)*" } });				// Equal sign

	std::vector <std::regex> temp;
	for (std::string gateName : gateNames) { temp.push_back(std::regex{ "^(\\s)*" + gateName + "(\\s)*" }); }		// Possible logical gate names
	regexList.push_back(temp);

	regexList.push_back({ std::regex{ "^\\((\\s)*" } });			// Opening parenthesis
	regexList.push_back({ std::regex{ "(\\s)*\\)(\\s)*$" } });		// Closing parenthesis

	regexList.push_back({ std::regex{ "^(\\s)*[a-z](\\s)*$" } });	// Input name



	// Creating the list of error messages
	std::vector<std::string> expressionErrors;
	expressionErrors.push_back("Expression must start with the name of the output (a single capital letter).");
	expressionErrors.push_back("Expecting the sign equal '=' after the name of the output (a single capital letter).");

	std::string gateNameError{ "Expecting the name of an input (a single lower case letter) or a logical door : " };
	for (std::string gateName : gateNames) { gateNameError.append(gateName + " "); }
	expressionErrors.push_back(gateNameError);

	expressionErrors.push_back("Expecting an opening parenthesis '(' after the name of a logical gate.");
	expressionErrors.push_back("Expecting a closing parenthesis ')' at the end of the expression.");




	// Checking the number of opening and closing parenthesis
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }
	}
	if (parenthesis != 0) { std::cout << "The number of parenthesis is incorrect." << std::endl; }

	
	bool expressionIsCorrect = false;
	//while(!expressionIsIncorrect) { redo the whole thing (including asking the user if they want to write their own expression)

	for (unsigned int i = OUTPUT_NAME; i <= EQUAL_SIGN; i++) {
		expressionIsCorrect = false;

		if (std::regex_search(expression, regexList.at(i).at(0) )) {
			expression = std::regex_replace(expression, regexList.at(i).at(0), "");
			expressionIsCorrect = true;
		}

		if (!expressionIsCorrect) {
			std::cout << expression << " - " << expressionErrors.at(i) << std::endl;
			break;
		}
	}

	expressionIsCorrect = checkGateExpression(expression, regexList, expressionErrors);

	std::cout << std::endl << std::endl;


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


bool checkGateExpression(std::string expression, const std::vector< std::vector <std::regex> > regexList, 
					const std::vector<std::string> expressionErrors) {


	// If the expression is an input
	if (std::regex_search(expression, regexList.at(INPUT_NAME).at(0))) { return true; }


	// Else if the expression is a logical gate, we check the name, the opening and closing parenthesis
	bool expressionIsCorrect = false;

	for (unsigned int i = GATE_NAME; i <= CLOSING_PARENTHESIS; i++) {
		expressionIsCorrect = false;

		// This is an OR loop : the expression only needs to verify one of the regex of each group to pass the test
		for (std::regex regex : regexList.at(i)) {
			if (std::regex_search(expression, regex)) {
				expression = std::regex_replace(expression, regex, "");
				expressionIsCorrect = true;
				break;
			}
		}

		if (!expressionIsCorrect) {
			std::cout << expression << " - " << expressionErrors.at(i) << std::endl;
			return false;
		}
	}



	// Recursive calls on the different parameters of the gate
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }

		// If there are 2 parameters
		else if (expression.at(i) == ',' && parenthesis == 0) {
			//std::cout << "2 attributes / inputs : " << expression.substr(0, i) 
			//	<< "         " << expression.substr(i + 1) << std::endl; // debug
			bool testLeft = checkGateExpression(expression.substr(0, i) , regexList, expressionErrors);
			bool testRight = checkGateExpression(expression.substr(i+1), regexList, expressionErrors);
			return (testLeft && testRight);
		}
	}

	// If there is only one parameter
	//std::cout << "One attribute / input : " << expression << std::endl; // debug
	return checkGateExpression(expression, regexList, expressionErrors);
}