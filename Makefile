EXECUTABLE = test
MAIN       = main
GRAPH      = graph
ALGORITHM  = algorithm

CPPFLAGS = -Wall -Wextra -Werror -pedantic

MODULES = \
	 $(MAIN) \
	 $(GRAPH) \
	 $(ALGORITHM)

OBJECTS := $(addsuffix .o, $(MODULES))
OBJECTS := $(addprefix bin/, $(OBJECTS))
SOURCES := $(addsuffix .cpp, $(MODULES))
SOURCES := $(addprefix src/, $(SOURCES))
HEADERS := $(addsuffix .hpp, $(MODULES))
HEADERS := $(addprefix include/, $(HEADERS))

$(EXECUTABLE): $(OBJECTS)
	g++ $^ -o $@ $(CPPFLAGS)

bin/$(MAIN).o: src/$(MAIN).cpp include/$(GRAPH).hpp include/$(ALGORITHM).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(GRAPH).o: src/$(GRAPH).cpp include/$(GRAPH).hpp include/$(ALGORITHM).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(ALGORITHM).o: src/$(ALGORITHM).cpp include/$(ALGORITHM).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin:
	mkdir -p bin

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) bin/*.o *.~
