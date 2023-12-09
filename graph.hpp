#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_set>
#include <ostream>

class Graph {
	public:
		Graph(const int &num_vertices, const std::vector<std::pair<int, int>> &edges);
		
		friend std::ostream& operator << (std::ostream &out, const Graph &g);
	private:
		std::vector<std::unordered_set<int>> _neighborhoods;
};

#endif
