#ifndef OUTPUT_GATE
#define OUTPUT_GATE

#include "../../Circuit/Drawing.hpp"
#include "IOGate.hpp"
#include "../LogicalGates/LogicalGate.hpp"
#include "../UpdateInterface.hpp"

class OutputGate final : public IOGate, UpdateInterface {
private:
	static const std::regex format;
	static const char defaultName;
	Gate* const gate;

	// CONSTRUCTORS
	OutputGate(const OutputGate& clone);
	OutputGate(const OutputGate* clone);	
	OutputGate();

public:
	OutputGate(const char name, Gate* const gate);

	// METHODS
	virtual void updateGate();
	virtual void drawGate(Drawing& d);

	// ACCESSORS
	Gate* const getGate() const;
};


// operator OVERLOAD
std::ostream& operator<<(std::ostream& out, const OutputGate* gate);

#endif

