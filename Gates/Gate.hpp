#ifndef GATE
#define GATE

#include "../Circuit/Drawing.hpp"

class Gate {
protected:
	bool value;
	bool alreadyUpdated;
	unsigned int gateLine;
	unsigned int gateColumn;
	std::string logicalFunction;

private:
	// CONSTRUCTORS
	Gate(const Gate& clone);
	Gate(const Gate* clone);

protected:
	Gate();

	// ACCESSORS
	void setValue(const bool value);
	void setLogicalFunction(const std::string function);

public:	
	// METHODS
	virtual void drawGate(Drawing& d) = 0;
	void draw(Drawing& d, const std::string s, const int offset);

	// ACCESSORS
	const bool getValue() const;
	const bool getAlreadyUpdated() const;
	const unsigned int getGateLine() const;
	const unsigned int getGateColumn() const;
	const std::string getLogicalFunction() const;

	void setAlreadyUpdated(const bool alreadyUpdated);
	void setGateLine(const int level);
	void setGateColumn(const int depth);
};


#endif
