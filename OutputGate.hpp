#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "IOGate.hpp"

class OutputGate : public IOGate {
private:
	static const std::regex format;
	static const std::string nomDefaut;

public:
	// CONSTRUCTEURS
	OutputGate(const std::string nom);
};

#endif

