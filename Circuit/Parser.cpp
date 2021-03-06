#include "Parser.hpp"

using namespace parser;

const int parser::OUTPUT_NAME{ 0 };
const int parser::EQUAL_SIGN{ 1 };
const int parser::GATE_NAME{ 2 };
const int parser::OPENING_PARENTHESIS{ 3 };
const int parser::CLOSING_PARENTHESIS{ 4 };
const int parser::INPUT_NAME{ 5 };
const int parser::PARAMETER_NUMBER{ 6 };

const int parser::GATE_NOT{ 0 };

const std::vector<std::string> parser::gateNames{ "not", "and", "or", "xor", "nor", "nand", "nxor"};
const std::vector< std::vector <std::regex> > parser::regexList{ createRegexList() };
const std::vector<std::string> parser::errorList{ createErrorMessages() };

std::vector<InputGate*> parser::inputGates{};
std::vector<LogicalGate*> parser::logicalGates{};
std::vector<OutputGate*> parser::outputGates{};


// Creating the list of regex used to check the expression
const std::vector< std::vector <std::regex> > parser::createRegexList() {
	std::vector< std::vector <std::regex> > regexListReturn;
	regexListReturn.push_back({ std::regex{ "^[A-Z]" } });						// Output name
	regexListReturn.push_back({ std::regex{ "^(\\s)*=(\\s)*" } });				// Equal sign

	std::vector <std::regex> temp;
	for (const std::string gateName : gateNames) { temp.push_back(std::regex{ "^(\\s)*" + gateName + "(\\s)*" }); }		// Possible logical gate names
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
	expressionErrorsReturn.push_back("Expecting the name of an input (a single lower case letter) or a logical gate.");
	expressionErrorsReturn.push_back("Expecting an opening parenthesis '(' before the parameter(s) of a logical gate.");
	expressionErrorsReturn.push_back("Expecting a closing parenthesis ')' after the parameter(s) of a logical gate.");
	expressionErrorsReturn.push_back("Expecting the name of an input (a single lower case letter).");
	expressionErrorsReturn.push_back("Incorrect number of parameters for this gate : expecting 1, two provided.");
	expressionErrorsReturn.push_back("Incorrect number of parameters for this gate : expecting 2, only one provided.");
	return expressionErrorsReturn;
}


// Asking the user for an input untill it matches what is expected
const std::string parser::userInput(const std::string message, const std::regex regex) {
	std::string input;
	int first = true;

	while (!std::regex_match(input, regex)) {
		if (first) { first = false; }
		else { std::cout << "Invalid value. "; }
		std::cout << message;
		std::cin >> input;
		std::cout << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	return input;
}

// Checking that the expression matches the syntax of a logical function
const bool parser::checkLogicalFunction(std::string expression) {

	// Checking the number of opening and closing parenthesis
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }
	}
	if (parenthesis != 0) {
		std::cout << expression << " --> The number of parenthesis is incorrect." << std::endl;
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
			std::cout << expression << " --> " << errorList.at(i) << std::endl;
			return false;
		}
	}
	return parser::checkGateExpression(expression);
}


// Checking the name and parameters of a logical gate / input (recursive function)
const bool parser::checkGateExpression(std::string expression) {

	// If the expression is an input
	if (std::regex_search(expression, regexList.at(INPUT_NAME).at(0))) { return true; }

	// Else checking if the expression matches a logical gate
	int gateType = -1;
	bool expressionIsCorrect = false;

	for (unsigned int j = 0; j < regexList.at(GATE_NAME).size(); j++) {
		if (std::regex_search(expression, regexList.at(GATE_NAME).at(j))) {
			expressionIsCorrect = true;
			gateType = j;
			expression = std::regex_replace(expression, regexList.at(GATE_NAME).at(j), "");
			break;
		}
	}

	if (!expressionIsCorrect) {
		std::cout << expression << " --> " << errorList.at(GATE_NAME) << std::endl;
		return false;
	}

	// Checking the opening and closing parenthesis
	for (unsigned int i = OPENING_PARENTHESIS; i <= CLOSING_PARENTHESIS; i++) {
		if (std::regex_search(expression, regexList.at(i).at(0))) {
			expression = std::regex_replace(expression, regexList.at(i).at(0), "");
		}
		else {
			std::cout << expression << " --> " << errorList.at(i) << std::endl;
			return false;
		}
	}

	// Recursive calls on the parameter(s) of the logical gate + checking that the number of parameters matches the gate type
	int parenthesis = 0;
	for (unsigned int i = 0; i < expression.size(); i++) {
		// Checking if all the parenthesis that were opened were also closed
		if (expression.at(i) == '(') { parenthesis = parenthesis + 1; }
		else if (expression.at(i) == ')') { parenthesis = parenthesis - 1; }

		// If there are 2 parameters
		else if (expression.at(i) == ',' && parenthesis == 0) {
			if (gateType == GATE_NOT) {
				std::cout << expression << " --> " << errorList.at(PARAMETER_NUMBER) << std::endl;
				return false;
			}
			bool testLeft = parser::checkGateExpression(expression.substr(0, i));
			if (!testLeft) { return testLeft; }

			bool testRight = parser::checkGateExpression(expression.substr(i + 1));
			return testRight;
		}
	}

	// If there is only one parameter
	if (gateType != GATE_NOT) {
		std::cout << expression << " --> " << errorList.at(PARAMETER_NUMBER + 1) << " " << std::endl;
		return false;
	}
	return parser::checkGateExpression(expression);
}

// Creating the circuit (must be done after having checked that the logical expression is correct)
Circuit* parser::createCircuit(std::string expression){

	// Getting the output gate name
	std::smatch match;
	std::string outputName;
	std::regex_search(expression, match, regexList.at(OUTPUT_NAME).at(0));
	outputName = match[0];

	// Removing the output gate name and the equal sign
	expression = std::regex_replace(expression, regexList.at(OUTPUT_NAME).at(0), "");
	expression = std::regex_replace(expression, regexList.at(EQUAL_SIGN).at(0), "");

	//Creating the output gate
	Gate* gate = parser::nextGates(expression);
	outputGates.push_back(new OutputGate(outputName[0], gate));
	return new Circuit(inputGates, logicalGates, outputGates);
}

// Creating gates from the name and parameters of a logical gate / input (recursive function)
Gate* const parser::nextGates(std::string expression) {
	// If the expression matches an input
	if (std::regex_search(expression, regexList.at(INPUT_NAME).at(0))) {
		std::smatch match;
		std::string inputName;
		std::regex_search(expression, match, std::regex{ "[a-z]" }); // Look for the input name without any white space
		inputName = match[0];

		for (InputGate* ig : inputGates) {
			if (ig->getName() == inputName[0]) {
				return ig;
			}
		}
		InputGate* input = new InputGate(inputName[0]);
		inputGates.push_back(input);
		return input;
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

// Creating a logical gate from its type and the list of its input(s)
Gate* const parser::createGate(const int gateType, std::vector<Gate*> const gates) {
	LogicalGate* lg;
	switch (gateType) {
	// The cases match the logical gate names in parser::gateNames (e.g. 0 = first cell of gateNames = "and")
	case 0:
		lg = new NotGate(gates.at(0));
		break;
	case 1:
		lg = new AndGate(gates.at(0), gates.at(1));
		break;
	case 2:
		lg = new OrGate(gates.at(0), gates.at(1));
		break;
	case 3:
		lg = new XorGate(gates.at(0), gates.at(1));
		break;
	case 4:
		lg = new NorGate(gates.at(0), gates.at(1));
		break;
	case 5:
		lg = new NandGate(gates.at(0), gates.at(1));
		break;
	case 6:
		lg = new NxorGate(gates.at(0), gates.at(1));
		break;
	}
	logicalGates.push_back(lg);
	return lg;
}