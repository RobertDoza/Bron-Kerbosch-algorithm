#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

#include "graph.hpp"
#include "set_ops.hpp"
#include "logger.hpp"

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

std::vector<int> Graph::degeneracy_ordering() const {
	unsigned n = _vertices.size();
	std::vector<int> l;
	std::vector<int> degrees(n);
	
	int max_degree = 0;
	for (const int v : _vertices) {
		degrees[v] = _neighborhoods[v].size();
		if (degrees[v] > max_degree) {
			max_degree = degrees[v];
		}
	}
	
	std::vector<std::unordered_set<int>> d(max_degree + 1);
	
	for (unsigned i = 0; i < n; i++) {
		d[degrees[i]].insert(i);
	}
	
	unsigned k = 0;
	for (unsigned _ = 0; _ < n; _++) {
		unsigned i;
		for (i = 0; i < d.size(); i++) {
			if (!d[i].empty()) {
				break;
			}
		}
		
		if (i > k) {
			k = i;
		}
		
		int v = *(d[i].begin());
		l.push_back(v);
		d[i].erase(v);
		
		for (auto w : _neighborhoods[v]) {
			if (std::find(l.begin(), l.end(), w) != l.end()) {
				continue;
			}
			
			d[degrees[w]].erase(w);
			degrees[w]--;
			d[degrees[w]].insert(w);
		}
	}
	
	return l;
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
