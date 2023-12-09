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
	
	std::cout << "\nPerforming algorithm...\n\n";
	
	g.perform_algorithm();
		
	return 0;
}
