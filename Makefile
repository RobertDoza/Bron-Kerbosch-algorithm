EXECUTABLE = test
MAIN       = main
GRAPH      = graph
SETOPS     = set_ops
LOGGER     = logger
SOLVE      = solve

BIN_DIR     = bin
SRC_DIR     = src
INCLUDE_DIR = include

CPPFLAGS = -Wall -Wextra -Werror -pedantic

MODULES = \
	 $(MAIN) \
	 $(GRAPH) \
	 $(SETOPS) \
	 $(LOGGER) \
	 $(SOLVE)

OBJECTS := $(addsuffix .o, $(MODULES))
OBJECTS := $(addprefix $(BIN_DIR)/, $(OBJECTS))

$(EXECUTABLE): $(OBJECTS)
	g++ $^ -o $@ $(CPPFLAGS)
	
$(BIN_DIR)/$(MAIN).o: $(SRC_DIR)/$(MAIN).cpp | $(BIN_DIR)
	g++ $< -c -o $@ $(CPPFLAGS) -I$(INCLUDE_DIR)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp | $(BIN_DIR)
	g++ $< -c -o $@ $(CPPFLAGS) -I$(INCLUDE_DIR)

$(BIN_DIR):
	mkdir -p $@

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(BIN_DIR)/*.o *.~
