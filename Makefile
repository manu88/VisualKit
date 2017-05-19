CC=g++

BUILD_CONFIG = -g -DDEBUG

CFLAGS= $(BUILD_CONFIG)  -c -Wall -Wextra 
CFLAGS+= -std=c++11 -pedantic 


CFLAGS+= -I/usr/local/include/GroundBase -I../GX/include/ -IVisualKit/

LDFLAGS= -L/usr/local/lib/ -L../GX/ -lGX -lGroundBase-cpp


SOURCES=$(wildcard VisualKit/*.cpp) $(wildcard Test1/*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= Test

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.cpp.o:
	@echo $(PLATFORM)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(EXECUTABLE)

re: clean all

