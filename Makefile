CC=gcc
CFLAGS=-c -Wall -g --std=c99
LDFLAGS=
SOURCES=./src/OnionPortScan.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=OnionPortScan

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
