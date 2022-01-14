#ifndef PARSER
#define PARSER

#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "AndGate.hpp"

#include <regex>


namespace parser {
	extern const int OUTPUT_NAME;
	extern const int EQUAL_SIGN;
	extern const int GATE_NAME;
	extern const int OPENING_PARENTHESIS;
	extern const int CLOSING_PARENTHESIS;
	extern const int INPUT_NAME;

	extern const std::vector<std::string> gateNames;
	extern const std::vector< std::vector <std::regex> > regexList;
	extern const std::vector<std::string> errorList;

	const std::vector< std::vector <std::regex> > createRegexList();
	const std::vector<std::string> createErrorMessages();
	const std::string userInput(const std::string message, const std::regex regex);
	const bool checkLogicalFunction(std::string expression);
	const bool checkGateExpression(std::string expression);
	void createCircuit(std::string expression);
	Gate* const nextGates(std::string expression);
	Gate* const createGate(const int gateType, std::vector<Gate*> const gates);
}

#endif