CC=g++
CPPLAGS=-g -Wall -O2
LDFLAGS=

SOURCES=main.cpp solutore.cpp soluzione.cpp istanza.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJECTS) main