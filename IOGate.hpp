#ifndef IO_GATE
#define IO_GATE

#include "Gate.hpp"

class IOGate : public Gate {
protected:
	std::string name;

	// CONSTRUCTEURS
	IOGate(const std::string name);

	// METHODES
	void checkNameFormating(const std::string name, const std::regex format, const std::string defaultName);

public:
	// ACCESSEURS
	// Mise en public de setValeur() pour les portes I/O
	using Gate::setValue;

	const std::string getName() const;
	void setName(const std::string name);
};



#endif