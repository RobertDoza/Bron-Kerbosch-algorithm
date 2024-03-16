#include <iostream>

#include "graph.hpp"
#include "algorithm.hpp"

int main() {
	std::vector<std::pair<int, int>> edges = {
		{0, 1},
		{0, 2},
		{1, 2},
		{1, 3},
		{4, 2},
		{6, 4},
		{4, 3}
	};

	Graph g(edges);
	
	std::cout << g;
	
	std::vector<int> degeneracy_ordering = g.degeneracy_ordering();
	std::cout << "degeneracy ordering: ";
	for (int v : degeneracy_ordering) {
		std::cout << v << " ";
	}
	std::cout << "\n";
		
	return 0;
}
