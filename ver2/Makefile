CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-std=c++11
SOURCES=player_text.cpp arbitr.cpp main.cpp common.cpp field.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=battle


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp *.h
	$(CC) $(CFLAGS) $< -o $@
