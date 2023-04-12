CXXFLAGS = -Wall -Wpedantic -Wextra -ggdb -std=gnu++11 -funsigned-char

SOURCES = $(wildcard *.cpp comm/*.cpp pltl/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = gop2

mingw: CXX = x86_64-w64-mingw32-g++
mingw: CXXFLAGS += -static

all: $(EXECUTABLE)

mingw: all

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE).exe $(OBJECTS)

.PHONY: all clean mingw
