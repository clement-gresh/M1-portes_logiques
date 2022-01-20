#include "IOGate.hpp"

// CONSTRUCTORS
// private
IOGate::IOGate(const IOGate& clone) : Gate{}, name{ ' ' } {}
IOGate::IOGate(const IOGate* clone) : Gate{}, name{ ' ' } {}
IOGate::IOGate() : Gate{}, name{ ' ' } {}

// protected
IOGate::IOGate(const char name) : Gate{}, name { name } {}

// METHODS
char IOGate::checkNameFormating(const char name, const std::regex format, const char defaultName) {
	if (!std::regex_match(std::string(1,name), format)) {
		std::cout << "Warning : the name \"" << name << "\" is invalid for this I/O gate. Name given instead : "
			<< defaultName << std::endl;
		return defaultName;
	}
	return name;
}

// ACCESSEURS
const char IOGate::getName() const { return name; }

