#include <iostream>

#include "graph.hpp"
#include "algorithm.hpp"

Graph::Graph(const std::vector<std::pair<int, int>> &edges) {
	_vertices = calculate_vertices(edges);

	_neighborhoods.resize(_vertices.size());

	for (const std::pair<int, int> &edge : edges) {
		int x = edge.first;
		int y = edge.second;
		
		_neighborhoods[x].insert(y);
		_neighborhoods[y].insert(x);
	}
}

void Graph::algorithm(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x) const {
	if (p.empty() && x.empty()) {
		std::cout << r << "\n";
		return;
	}
	
	auto it = p.begin();
	while (it != p.end()) {
		int v = *it;
		
		std::unordered_set<int> new_r = r;
		new_r.insert(v);
		std::unordered_set<int> new_p = set_intersection(p, _neighborhoods[v]);
		std::unordered_set<int> new_x = set_intersection(x, _neighborhoods[v]);
		
		algorithm(new_r, new_p, new_x);
		
		it = p.erase(it);
		x.insert(v);
	}
}

void Graph::perform_algorithm() const {
	std::unordered_set<int> r = {};
	std::unordered_set<int> p = _vertices;
	std::unordered_set<int> x = {};

	algorithm(r, p, x);
}

std::ostream& operator << (std::ostream &out, const Graph &g) {
	out << "vertices: " << g._vertices << "\n";

	for (const std::unordered_set<int> &neighborhood : g._neighborhoods) {	
		out << neighborhood << "\n";
	}
	
	return out; 
}

std::unordered_set<int> Graph::calculate_vertices(const std::vector<std::pair<int, int>> &edges) {
	if (edges.empty()) {
		return {};
	}
	
	int max = edges[0].first;
	for (const std::pair<int, int> &edge : edges) {
		int x = edge.first;
		int y = edge.second;
		
		if (x > max) {
			max = x;
		}
		
		if (y > max) {
			max = y;
		}
	}
	
	std::unordered_set<int> vertices = {};
	for (int i = 0; i <= max; i++) {
		vertices.insert(i);
	}
	
	return vertices;
}
