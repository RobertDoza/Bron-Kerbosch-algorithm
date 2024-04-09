#include <iostream>

#include "graph.hpp"
#include "set_ops.hpp"

int main() {
	try {
		Graph g("data/wiki.txt");
		
		// std::cout << g;
		
		g.perform_algorithm();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
