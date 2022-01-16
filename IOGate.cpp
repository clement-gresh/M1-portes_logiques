#include "IOGate.hpp"

// CONSTRUCTORS
IOGate::IOGate(const char name) : Gate{}, name { name } {}

// METHODS
char IOGate::checkNameFormating(const char name, const std::regex format, const char defaultName) {
	if (!std::regex_match(&name, format)) {
		std::cout << "Attention : le nom \"" << name << "\" est invalide pour cette porte I/O. Nom donne a la porte : "
			<< defaultName << std::endl;
		return defaultName;
	}
	return name;
}


// ACCESSEURS
const char IOGate::getName() const { return name; }

