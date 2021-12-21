#ifndef IO_GATE
#define IO_GATE

#include "Gate.hpp"

class IOGate : public Gate {
protected:
	char name;

	// CONSTRUCTEURS
	IOGate(const char name);

	// METHODES
	void checkNameFormating(const char name, const std::regex format, const char defaultName);

public:
	// ACCESSEURS
	// Mise en public de setValeur() pour les portes I/O
	using Gate::setValue;

	const char getName() const;
	void setName(const char name);
};



#endif