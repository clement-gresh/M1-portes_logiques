#ifndef GATE
#define GATE

#include <string>
#include <iostream>
#include <regex>

class Gate {
protected:
	bool valeur;

	// CONSTRUCTEURS
	Gate();
	Gate(const Gate& clone);
	Gate(const Gate* clone);

	// ACCESSEURS
	void setValeur(const bool valeur);

public:
	const bool getValeur() const;
};


#endif