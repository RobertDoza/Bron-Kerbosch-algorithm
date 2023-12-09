#include "graph.hpp"

Graph::Graph(const int &num_vertices, const std::vector<std::pair<int, int>> &edges) {
	_neighborhoods.resize(num_vertices);

	for (const std::pair<int, int> &edge : edges) {
		int x = edge.first;
		int y = edge.second;
		
		_neighborhoods[x].insert(y);
		_neighborhoods[y].insert(x);
	}
}

std::ostream& operator << (std::ostream &out, const Graph &g) {
	for (const std::unordered_set<int> &neighborhood : g._neighborhoods) {	
		if (neighborhood.empty()) {
			out << "{}\n";
			continue;
		}
	
		out << "{";
		
		for (const int &vertex : neighborhood) {
			out << vertex << ", ";
		}
		
		out << "\b\b}\n";
	}
	
	return out; 
}
