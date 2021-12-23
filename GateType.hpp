#ifndef GATE_TYPE
#define GATE_TYPE

#include <iostream>

enum class GateType { DEFAULT, INPUT, OUTPUT, AND };

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
