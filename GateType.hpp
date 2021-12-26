#ifndef GATE_TYPE
#define GATE_TYPE

#include <iostream>

enum class GateType { DEFAULT, INPUT, OUTPUT, AND };

inline std::string operator+(std::string gateName, GateType type) {
	switch (type) {
		case GateType::DEFAULT: gateName = "DEF"; break;
		case GateType::INPUT: gateName = "INP"; break;
		case GateType::OUTPUT: gateName = "OUT"; break;
		case GateType::AND: gateName = "AND"; break;
	}
	return gateName;
}


inline std::string operator*(GateType type, std::string logicalFunction) {
	switch (type) {
	case GateType::DEFAULT: logicalFunction = "def"; break;
	case GateType::INPUT: logicalFunction = "inp"; break;
	case GateType::OUTPUT: logicalFunction = "out"; break;
	case GateType::AND: logicalFunction = "and"; break;
	}
	return logicalFunction;
}

inline std::ostream& operator<<(std::ostream& out, GateType type) {
	switch (type) {
		case GateType::DEFAULT: out << "DEFAULT"; break;
		case GateType::INPUT: out << "INPUT"; break;
		case GateType::OUTPUT: out << "OUTPUT"; break;
		case GateType::AND: out << "AND"; break;
	}
	return out;
}

#endif
