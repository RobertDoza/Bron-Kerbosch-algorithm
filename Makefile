EXECUTABLE = test
MAIN       = main
GRAPH      = graph
SETOPS     = set_ops
LOGGER     = logger
SOLVE      = solve

CPPFLAGS = -Wall -Wextra -Werror -pedantic

MODULES = \
	 $(MAIN) \
	 $(GRAPH) \
	 $(SETOPS) \
	 $(LOGGER) \
	 $(SOLVE)

OBJECTS := $(addsuffix .o, $(MODULES))
OBJECTS := $(addprefix bin/, $(OBJECTS))
SOURCES := $(addsuffix .cpp, $(MODULES))
SOURCES := $(addprefix src/, $(SOURCES))
HEADERS := $(addsuffix .hpp, $(MODULES))
HEADERS := $(addprefix include/, $(HEADERS))

$(EXECUTABLE): $(OBJECTS)
	g++ $^ -o $@ $(CPPFLAGS)

bin/$(MAIN).o: src/$(MAIN).cpp include/$(GRAPH).hpp include/$(SETOPS).hpp include/$(SOLVE).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(GRAPH).o: src/$(GRAPH).cpp include/$(GRAPH).hpp include/$(SETOPS).hpp include/$(LOGGER).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(SETOPS).o: src/$(SETOPS).cpp include/$(SETOPS).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(LOGGER).o: src/$(LOGGER).cpp include/$(LOGGER).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin/$(SOLVE).o: src/$(SOLVE).cpp include/$(SOLVE).hpp include/$(LOGGER).hpp include/$(SETOPS).hpp | bin
	g++ $< -c -o $@ $(CPPFLAGS) -Iinclude

bin:
	mkdir -p bin

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) bin/*.o *.~
