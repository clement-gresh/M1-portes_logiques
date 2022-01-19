CPP=g++ --std=c++11
CFLAGS= -Wall

all : circuit

circuit : Source.o Parser.o Circuit.o Drawing.o Gate.o IOGate.o InputGate.o OutputGate.o LogicalGate.o AndGate.o NandGate.o NorGate.o NotGate.o NxorGate.o OrGate.o XorGate.o
	$(CPP) $(CFLAGS) -o $@ $^



# Source and circuit
Source.o : Source.cpp
	$(CPP) $(CFLAGS) -c $<

Parser.o : ./Circuit/Parser.cpp ./Circuit/Parser.hpp
	$(CPP) $(CFLAGS) -c $<

Circuit.o : ./Circuit/Circuit.cpp ./Circuit/Circuit.hpp
	$(CPP) $(CFLAGS) -c $<

Drawing.o : ./Circuit/Drawing.cpp ./Circuit/Drawing.hpp
	$(CPP) $(CFLAGS) -c $<


# Gate
Gate.o : ./Gates/Gate.cpp ./Gates/Gate.hpp
	$(CPP) $(CFLAGS) -c $<
	

# IOGate
IOGate.o : ./Gates/IOGates/IOGate.cpp ./Gates/IOGates/IOGate.hpp
	$(CPP) $(CFLAGS) -c $<
	
InputGate.o : ./Gates/IOGates/InputGate.cpp ./Gates/IOGates/InputGate.hpp
	$(CPP) $(CFLAGS) -c $<

OutputGate.o : ./Gates/IOGates/OutputGate.cpp ./Gates/IOGates/OutputGate.hpp ./Gates/UpdateInterface.hpp
	$(CPP) $(CFLAGS) -c $<


# LogicalGate
LogicalGate.o : ./Gates/LogicalGates/LogicalGate.cpp ./Gates/LogicalGates/LogicalGate.hpp ./Gates/UpdateInterface.hpp
	$(CPP) $(CFLAGS) -c $<

AndGate.o : ./Gates/LogicalGates/AndGate.cpp ./Gates/LogicalGates/AndGate.hpp
	$(CPP) $(CFLAGS) -c $<

NandGate.o : ./Gates/LogicalGates/NandGate.cpp ./Gates/LogicalGates/NandGate.hpp
	$(CPP) $(CFLAGS) -c $<

NorGate.o : ./Gates/LogicalGates/NorGate.cpp ./Gates/LogicalGates/NorGate.hpp
	$(CPP) $(CFLAGS) -c $<

NotGate.o : ./Gates/LogicalGates/NotGate.cpp ./Gates/LogicalGates/NotGate.hpp
	$(CPP) $(CFLAGS) -c $<

NxorGate.o : ./Gates/LogicalGates/NxorGate.cpp ./Gates/LogicalGates/NxorGate.hpp
	$(CPP) $(CFLAGS) -c $<

OrGate.o : ./Gates/LogicalGates/OrGate.cpp ./Gates/LogicalGates/OrGate.hpp
	$(CPP) $(CFLAGS) -c $<

XorGate.o : ./Gates/LogicalGates/XorGate.cpp ./Gates/LogicalGates/XorGate.hpp
	$(CPP) $(CFLAGS) -c $<



clean :
	rm *.o

test: all
	./circuit
