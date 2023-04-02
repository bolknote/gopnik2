CC=g++
CFLAGS=-Wall -Wpedantic -Wextra -ggdb
LDFLAGS=

SOURCES=$(wildcard *.cpp comm/*.cpp pltl/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gop2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
