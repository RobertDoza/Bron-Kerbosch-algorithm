#include <iostream>

#include "graph.hpp"

int main() {
	int num_vertices = 7;
	
	std::vector<std::pair<int, int>> edges = {
		{0, 1},
		{0, 2},
		{1, 2},
		{1, 3},
		{4, 2},
		{6, 4},
		{4, 3}
	};

	Graph g(num_vertices, edges);
	
	std::cout << g;
	
	return 0;
}
