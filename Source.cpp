#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"
#include "Circuit.hpp"

#include <regex>


const std::vector< std::vector <std::regex> > createRegexList();
const std::vector<std::string> createErrorMessages();
//static const std::string userInput(const std::string message, const std::regex regex);
bool checkLogicalFunction(std::string expression);
bool checkGateExpression(std::string expression);
void createCircuit(std::string expression);
Gate* const nextGates(std::string expression);
Gate* const createGate(const int gateType, std::vector<Gate*> const gates);


const int OUTPUT_NAME = 0;
const int EQUAL_SIGN = 1;
const int GATE_NAME = 2;
const int OPENING_PARENTHESIS = 3;
const int CLOSING_PARENTHESIS = 4;
const int INPUT_NAME = 5;

const std::vector<std::string> gateNames = { "and", "or" };

const std::vector< std::vector <std::regex> > regexList{ createRegexList() };
const std::vector<std::string> errorList{ createErrorMessages() };


int main(int argc, char** argv)
{
	// Asking the user to enter the logical expression of the circuit
	std::string s = "Do you want to write down the logical expression of the circuit (e.g. \"A = or( a, and (b ,c) )\") ?\n";
	s = s + "Otherwise the default circuit will be loaded. (y / n) ";

	std::string input = Circuit::userInput(s, std::regex{ "^[yn]$" });

	// Checking the syntax of the logical expression entered by the user
	if (input.compare("y") == 0) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		bool expressionIsCorrect = false;

		while (!expressionIsCorrect) {
			std::cout << "Enter the logical expression of the circuit (type 'exit' to load the default circuit) : ";
			std::getline(std::cin, input);

			if (input.compare("exit") == 0) { break; }
		
			expressionIsCorrect = checkLogicalFunction(input);
			std::cout << std::endl;
		}


		if (expressionIsCorrect) {
			std::cout << "The syntax of the expression is correct, now creating the circuit." << std::endl;
			createCircuit(input);
			return 0;
		}
	}

	std::cout << std::endl << "Loading pre-existing circuit." << std::endl;


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


// Creating the list of regex used to check the expression
const std::vector< std::vector <std::regex> > createRegexList() {
	std::vector< std::vector <std::regex> > regexListReturn;

	regexListReturn.push_back({ std::regex{ "^[A-Z]" } });						// Output name
	regexListReturn.push_back({ std::regex{ "^(\\s)*=(\\s)*" } });				// Equal sign

	std::vector <std::regex> temp;
	for (std::string gateName : gateNames) { temp.push_back(std::regex{ "^(\\s)*" + gateName + "(\\s)*" }); }		// Possible logical gate names
	regexListReturn.push_back(temp);

	regexListReturn.push_back({ std::regex{ "^(\\s)*\\((\\s)*" } });			// Opening parenthesis
	regexListReturn.push_back({ std::regex{ "(\\s)*\\)(\\s)*$" } });			// Closing parenthesis

	regexListReturn.push_back({ std::regex{ "^(\\s)*[a-z](\\s)*$" } });			// Input name

	return regexListReturn;
}


// Creating the list of error messages corresponding to the regex used to check the expression
const std::vector<std::string> createErrorMessages() {
	std::vector<std::string> expressionErrorsReturn;

	expressionErrorsReturn.push_back("Expression must start with the name of the output (a single capital letter).");
	expressionErrorsReturn.push_back("Expecting the sign equal '=' after the name of the output (a single capital letter).");

	std::string gateNameError{ "Expecting the name of an input (a single lower case letter) or a logical door : " };
	for (std::string gateName : gateNames) { gateNameError.append(gateName + " "); }
	expressionErrorsReturn.push_back(gateNameError);

	expressionErrorsReturn.push_back("Expecting an opening parenthesis '(' before the parameter(s) of a logical gate.");
	expressionErrorsReturn.push_back("Expecting a closing parenthesis ')' after the parameter(s) of a logical gate.");

	return expressionErrorsReturn;
}


bool checkLogicalFunction(std::string expression) {

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
			std::cout << expression << " - " << errorList.at(i) << std::endl;
			return false;
		}
	}

	
	return checkGateExpression(expression);
}


// Checking the name and parameters a logical gate / input (recursiv function)
bool checkGateExpression(std::string expression) {

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
			std::cout << expression << " --> " << errorList.at(i) << std::endl;
			return false;
		}
	}



	// Recursive calls on the parameter(s) of the logical gate
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		// Checking if all the parenthesis that were opened were also closed
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }

		// If there are 2 parameters
		else if (expression.at(i) == ',' && parenthesis == 0) {
			bool testLeft = checkGateExpression(expression.substr(0, i));
			if (!testLeft) { return testLeft; }

			bool testRight = checkGateExpression(expression.substr(i+1));
			return testRight;
		}
	}

	// If there is only one parameter
	return checkGateExpression(expression);
}


// Creating the circuit (must be done after having checked that the logical expression is correct)
void createCircuit(std::string expression) {

	// Getting the output gate name
	std::smatch match;
	std::string outputName;

	std::regex_search(expression, match, regexList.at(OUTPUT_NAME).at(0));
	outputName = match[0];

	expression = std::regex_replace(expression, regexList.at(OUTPUT_NAME).at(0), "");


	// Removing the equal sign from the expression
	expression = std::regex_replace(expression, regexList.at(EQUAL_SIGN).at(0), "");
	
	//Creating the output gate
	Gate* gate = nextGates(expression);
	OutputGate* output = new OutputGate(outputName[0], gate);
}


Gate* const nextGates(std::string expression) {

	std::cout << "Call to nextGate() with expression : " << expression << std::endl;

	// If the expression matches an input
	if (std::regex_search(	expression,	regexList.at(INPUT_NAME).at(0))) {
		std::smatch match;
		std::string inputName;

		std::regex_search(expression, match, std::regex{ "[a-z]" }); // Look for the input name without any white space
		inputName = match[0];

		return new InputGate(inputName[0]);
	}


	// Else finding what kind of logical gate the expression matches
	int gateType = -1;
	for (unsigned int j = 0; j < regexList.at(GATE_NAME).size(); j++) {
		if (std::regex_search(expression, regexList.at(GATE_NAME).at(j))) {
			gateType = j;
			expression = std::regex_replace(expression, regexList.at(GATE_NAME).at(j), "");
			break;
		}
	}


	// Removing the parenthesis
	for (unsigned int i = OPENING_PARENTHESIS; i <= CLOSING_PARENTHESIS; i++) {
		expression = std::regex_replace(expression, regexList.at(i).at(0), "");
	}


	// Recursive calls on the parameter(s) of the logical gate
	std::vector<Gate*> gates;
	int parenthesis = 0;
	bool oneParameter = true;
	for (unsigned int i = 0; i < expression.size(); i++) {
		// Checking if all the parenthesis that were opened were also closed
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }

		// If there are 2 parameters
		else if (expression.at(i) == ',' && parenthesis == 0) {
			oneParameter = false;
			Gate* gateLeft = nextGates(expression.substr(0, i));
			Gate* gateRight = nextGates(expression.substr(i + 1));
			gates.push_back(gateLeft);
			gates.push_back(gateRight);
		}
	}

	// If there is only one parameter
	if (oneParameter) {
		Gate* onlyGate = nextGates(expression);
		gates.push_back(onlyGate);
	}

	return createGate(gateType, gates);
}


Gate* const createGate(const int gateType, std::vector<Gate*> const gates) {
	switch (gateType) {
		case 0:
			return new AndGate(gates.at(0), gates.at(1));
	}
}
