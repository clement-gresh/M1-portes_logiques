#include "IOGate.hpp"

// CONSTRUCTORS
IOGate::IOGate(const char name) : Gate{}, name { name } {
	std::cout << "Construction d'une porte entree/sortie : " << name << std::endl; // debug
}

// METHODS
void IOGate::checkNameFormating(const char name, const std::regex format, const char defaultName) {
	if (!std::regex_match(&name, format)) {
		this->name = defaultName;
		std::cout << "Attention : le nom \"" << name << "\" est invalide pour cette porte I/O. Nom donne a la porte : " << defaultName << std::endl;
	}
}


// ACCESSEURS
const char IOGate::getName() const { return name; }