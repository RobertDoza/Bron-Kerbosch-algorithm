#include <iostream>

#include "graph.hpp"
#include "algorithm.hpp"

int main() {
	try {
		Graph g("graph.txt");
		
		std::cout << g;
		
		std::vector<int> degeneracy_ordering = g.degeneracy_ordering();
		std::cout << "degeneracy ordering: ";
		for (int v : degeneracy_ordering) {
			std::cout << v << " ";
		}
		std::cout << "\n";
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
