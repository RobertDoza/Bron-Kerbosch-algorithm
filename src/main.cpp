#include <iostream>

#include "graph.hpp"
#include "set_ops.hpp"
#include "solve.hpp"

int main() {
	try {
		Graph g("assets/blue_graph.txt");
		
		// std::cout << g;
		
		perform_algorithm(g, AlgType::BASIC);
		perform_algorithm(g, AlgType::PIVOTING);
		perform_algorithm(g, AlgType::DEGEN_ORDERING);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
