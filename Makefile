CXXFLAGS+=-Wall -Wpedantic -Wextra -ggdb
LDFLAGS=

SOURCES=$(wildcard *.cpp comm/*.cpp pltl/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gop2

all: $(SOURCES) $(EXECUTABLE)

mingw:
	CXX=i686-w64-mingw32-g++ CXXFLAGS=-static make

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE).exe $(OBJECTS)

.PHONY: all clean mingw
