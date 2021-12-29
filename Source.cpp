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

const std::vector<std::string> gateNames = { "and", "or" };


bool checkLogicalFunction(std::string expression);
bool checkGateExpression(std::string expression, const std::vector< std::vector <std::regex> > regexList,
	const std::vector<std::string> expressionErrors);


int main(int argc, char** argv)
{
	// Asking the user to enter the logical expression of the circuit
	std::cout << "Do you want to write down the logical expression of the circuit (e.g. \"A = or( a, and (b ,c) )\") ? "
		<<  "Otherwise the default circuit will be loaded. (y/n) ";
	std::string enterExpression;
	std::cin >> enterExpression;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << std::endl;

	while (enterExpression.compare("y") != 0 && enterExpression.compare("n") != 0) {
		std::cout << "Invalid value! Do you want to write down the logical expression of the circuit? (y/n) ";
		std::cin >> enterExpression;
		//std::getline(std::cin, enterExpression);
	}

	// Checking the syntax of the logical expression entered by the user
	if (enterExpression.compare("y") == 0) {
		bool expressionIsCorrect = false;

		while (!expressionIsCorrect) {
			std::cout << "Enter the logical expression of the circuit (type 'exit' to load the default circuit) : ";
			std::string expression;
			std::getline(std::cin, expression);

			if (expression.compare("exit") == 0) { break; }
		
			expressionIsCorrect = checkLogicalFunction(expression);
			std::cout << std::endl;
		}
		
	}

	std::cout << std::endl;


	InputGate* a = new InputGate('a');
	InputGate* b = new InputGate('w');
	InputGate* c = new InputGate('c');
	InputGate* d = new InputGate('F');
	AndGate* orr = new AndGate(a, b);
	AndGate* and1 = new AndGate(c, d);
	AndGate* and2 = new AndGate(b , d);
	AndGate* and3 = new AndGate(a, a);
	AndGate* and4 = new AndGate(and1, and3);
	AndGate* and5 = new AndGate(orr, and2);
	AndGate* and6 = new AndGate(and4, and5);
	OutputGate* A = new OutputGate('A', orr);
	OutputGate* B = new OutputGate('d', and3);
	OutputGate* C = new OutputGate('C', and6);

	std::vector<InputGate*> inputGates = { a, b, c, d };
	std::vector<LogicalGate*> logicalGates = { orr, and1, and3, and4, and5, and6 };
	std::vector<OutputGate*> outputGates = { A, B, C };
	
	Circuit* circuit1 = new Circuit(inputGates, logicalGates, outputGates);

	circuit1->addLogicalGate(and2);

	circuit1->simulateCircuit();

	return 0;
}


bool checkLogicalFunction(std::string expression) {

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

	expressionErrors.push_back("Expecting an opening parenthesis '(' before the parameter(s) of a logical gate.");
	expressionErrors.push_back("Expecting a closing parenthesis ')' after the parameter(s) of a logical gate.");




	// Checking the number of opening and closing parenthesis
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }
	}
	if (parenthesis != 0) { 
		std::cout << "The number of parenthesis is incorrect." << std::endl;
		return false;
	}


	// Checking output name and the equal sign (e.g. "C = ..." )
	for (unsigned int i = OUTPUT_NAME; i <= EQUAL_SIGN; i++) {
		bool expressionIsCorrect = false;

		if (std::regex_search(expression, regexList.at(i).at(0))) {
			expression = std::regex_replace(expression, regexList.at(i).at(0), "");
			expressionIsCorrect = true;
		}

		if (!expressionIsCorrect) {
			std::cout << expression << " - " << expressionErrors.at(i) << std::endl;
			return false;
		}
	}

	
	return checkGateExpression(expression, regexList, expressionErrors);
}


// Checking the name and parameters a logical gate / input (recursiv function)
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
			bool testLeft = checkGateExpression(expression.substr(0, i) , regexList, expressionErrors);
			if (!testLeft) { return testLeft; }

			bool testRight = checkGateExpression(expression.substr(i+1), regexList, expressionErrors);
			return testRight;
		}
	}

	// If there is only one parameter
	return checkGateExpression(expression, regexList, expressionErrors);
}