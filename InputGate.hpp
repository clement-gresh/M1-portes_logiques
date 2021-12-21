#ifndef INPUT_GATE
#define INPUT_GATE

#include "IOGate.hpp"

class InputGate : public IOGate {
private:
	static const std::regex format;
	static const std::string nomDefaut;

public:
    // CONSTRUCTEURS
    InputGate(const std::string nom);

	// ACCESSEURS
	// Mise en public de setValeur() pour les portes d'entree
	using Gate::setValeur;
};

#endif