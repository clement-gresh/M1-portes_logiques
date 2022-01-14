#include "Parser.hpp"

using namespace parser;


const int parser::OUTPUT_NAME{ 0 };
const int parser::EQUAL_SIGN{ 1 };
const int parser::GATE_NAME{ 2 };
const int parser::OPENING_PARENTHESIS{ 3 };
const int parser::CLOSING_PARENTHESIS{ 4 };
const int parser::INPUT_NAME{ 5 };

const std::vector<std::string> parser::gateNames{ { "and", "or" } };
const std::vector< std::vector <std::regex> > parser::regexList{ createRegexList() };
const std::vector<std::string> parser::errorList{ createErrorMessages() };



// Creating the list of regex used to check the expression
const std::vector< std::vector <std::regex> > parser::createRegexList() {
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
const std::vector<std::string> parser::createErrorMessages() {
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


// Asking the user for an input untill it matches what is expected
const std::string parser::userInput(const std::string message, const std::regex regex) {
	std::string input;
	int first = true;

	while (!std::regex_match(input, regex)) {
		if (first) { first = false; }
		else { std::cout << std::endl << "Invalid value. "; }
		std::cout << message;
		std::cin >> input;
	}
	return input;
}



const bool parser::checkLogicalFunction(std::string expression) {

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


	return parser::checkGateExpression(expression);
}


// Checking the name and parameters a logical gate / input (recursiv function)
const bool parser::checkGateExpression(std::string expression) {

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
			bool testLeft = parser::checkGateExpression(expression.substr(0, i));
			if (!testLeft) { return testLeft; }

			bool testRight = parser::checkGateExpression(expression.substr(i + 1));
			return testRight;
		}
	}

	// If there is only one parameter
	return parser::checkGateExpression(expression);
}


// Creating the circuit (must be done after having checked that the logical expression is correct)
void parser::createCircuit(std::string expression) {

	// Getting the output gate name
	std::smatch match;
	std::string outputName;

	std::regex_search(expression, match, regexList.at(OUTPUT_NAME).at(0));
	outputName = match[0];

	// Removing the output gate name and the equal sign from the expression
	expression = std::regex_replace(expression, regexList.at(OUTPUT_NAME).at(0), "");
	expression = std::regex_replace(expression, regexList.at(EQUAL_SIGN).at(0), "");

	//Creating the output gate
	Gate* gate = parser::nextGates(expression);
	OutputGate* output = new OutputGate(outputName[0], gate);
}


Gate* const parser::nextGates(std::string expression) {

	std::cout << "Call to nextGate() with expression : " << expression << std::endl; // debug

	// If the expression matches an input
	if (std::regex_search(expression, regexList.at(INPUT_NAME).at(0))) {
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
		// Checking when all the parenthesis that were opened are closed
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }

		// If there are 2 parameters
		else if (expression.at(i) == ',' && parenthesis == 0) {
			oneParameter = false;
			Gate* gateLeft = parser::nextGates(expression.substr(0, i));
			Gate* gateRight = parser::nextGates(expression.substr(i + 1));
			gates.push_back(gateLeft);
			gates.push_back(gateRight);
		}
	}

	// If there is only one parameter
	if (oneParameter) {
		Gate* onlyGate = parser::nextGates(expression);
		gates.push_back(onlyGate);
	}

	return parser::createGate(gateType, gates);
}


Gate* const parser::createGate(const int gateType, std::vector<Gate*> const gates) {
	switch (gateType) {
	case 0:
		return new AndGate(gates.at(0), gates.at(1));
	}
}