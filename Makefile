EXECUTABLE = test
MAIN = main
GRAPH = graph
ALGORITHM = algorithm
CPPFLAGS = -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(GRAPH).o $(ALGORITHM).o
	g++ $^ -o $@ $(CPPFLAGS)

$(MAIN).o: $(MAIN).cpp $(GRAPH).hpp $(ALGORITHM).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(GRAPH).o: $(GRAPH).cpp $(GRAPH).hpp $(ALGORITHM).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(ALGORITHM).o: $(ALGORITHM).cpp $(ALGORITHM).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *.~
