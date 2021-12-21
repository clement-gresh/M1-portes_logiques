#include "IOGate.hpp"

// CONSTRUCTORS
IOGate::IOGate(const std::string name) : Gate{}, name { name } {
	std::cout << "Construction d'une porte entree/sortie : " << name << std::endl; // debug
}


// METHODS
void IOGate::checkNameFormating(const std::string name, const std::regex format, const std::string defaultName) {
	if (!std::regex_match(name, format)) {
		this->name = defaultName;
		std::cout << "Attention : le nom \"" << name << "\" est invalide pour cette porte I/O. Nom donne a la porte : " << defaultName << std::endl;
	}
}


// ACCESSEURS
const std::string IOGate::getName() const { return name; }

void IOGate::setName(const std::string name) { this->name = name; }