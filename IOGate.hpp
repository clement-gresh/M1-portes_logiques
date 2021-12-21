#ifndef IO_GATE
#define IO_GATE

#include "Gate.hpp"

class IOGate : public Gate {
protected:
	std::string nom;

	// CONSTRUCTEURS
	IOGate(const std::string nom);

public:
	// ACCESSEURS
	// Mise en public de setValeur() pour les portes I/O
	using Gate::setValeur;

	const std::string getNom() const;
	void setNom(const std::string nom);
};

#endif