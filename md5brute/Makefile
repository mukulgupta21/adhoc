# Compiler
CXX=g++
# Compiler flags
CXXFLAGS=-c -Wall
# Linker
LDFLAGS=-lcrypto

# Sources
SOURCES=$(wildcard *.cpp)

# Object files
OBJECTS=$(SOURCES:.cpp=.o)

# Name of the executable
EXECUTABLE=md5brute

# $^ - pre-requisites
# $@ - target
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
