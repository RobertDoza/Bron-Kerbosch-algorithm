#include <iostream>
#include <fstream>

#include "graph.hpp"
#include "set_ops.hpp"

Graph::Graph(const std::string &filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("Error - failed to open file: " + filename);
	}

	int n;
	file >> n;

	if (n < 0) {
		throw std::runtime_error("Error - invalid number of vertices: " + std::to_string(n));
	}

	std::vector<std::vector<int>> adjacency_matrix(n);
	for (int i = 0; i < n; i++) {
		adjacency_matrix[i].resize(n);
		for (int j = 0; j < n; j++) {
			int elem;
			file >> elem;
			
			if (elem != 0 && elem != 1) {
				throw std::runtime_error("Error - adjacency matrix must contain only 1s and 0s!");
			}
			
			adjacency_matrix[i][j] = elem;
		}
	}

	for (int i = 0; i < n; i++) {
		_vertices.insert(i);
	}
	
	_neighborhoods.resize(n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
				throw std::runtime_error("Error - adjacency matrix is asymmetric!");
			}
			
			if (adjacency_matrix[i][j]) {
				_neighborhoods[i].insert(j);
				_neighborhoods[j].insert(i);
			}
		}
	}
}

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

std::unordered_set<int> Graph::get_vertices() const {
	return _vertices;
}

std::unordered_set<int> Graph::get_neighborhood(int u) const {
	return _neighborhoods[u];
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
