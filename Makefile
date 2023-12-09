EXECUTABLE = test
MAIN = main
GRAPH = graph
CPPFLAGS = -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(GRAPH).o
	g++ $^ -o $@ $(CPPFLAGS)

$(MAIN).o: $(MAIN).cpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(GRAPH).o: $(GRAPH).cpp $(GRAPH).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *.~
