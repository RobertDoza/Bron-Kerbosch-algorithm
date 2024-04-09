#include <iostream>
#include <sstream>
#include <algorithm>
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
	
	// TODO: remove output
	/*
	for (const auto &set : d) {
		std::cout << set << std::endl;
	}
	*/
	
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
		
		// TODO: remove output
		// std::cout << "\nv = " << v << "\n";
		for (auto w : _neighborhoods[v]) {
			if (std::find(l.begin(), l.end(), w) != l.end()) {
				continue;
			}
			
			d[degrees[w]].erase(w);
			degrees[w]--;
			d[degrees[w]].insert(w);
		}
		
		// TODO: remove output
		/*
		for (const auto &set : d) {
			std::cout << set << std::endl;
		}
		*/
		
	}
	
	// TODO: remove output
	/*
	std::cout << "l: ";
	for (int v : l) {
		std::cout << v << " ";
	}
	std::cout << "\n";
	std::cout << "k = " << k << "\n";
	*/
	
	return l;
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

void Graph::bron_kerbosch(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x) const {
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
		
		bron_kerbosch(new_r, new_p, new_x);
		
		it = p.erase(it);
		x.insert(v);
	}
}

void Graph::bron_kerbosch_2(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x, const int &depth) const {
	std::cout << indentation(depth);
	std::cout << "R = " << r << ", P = " << p << ", X = " << x << "\n";

	if (p.empty() && x.empty()) {
		std::cout << indentation(depth) << "found clique: " << r << "\n";
		std::cout << indentation(depth) << "STOP\n";
		return;
	}
	
	int u = 0;
	int max_size = 0;
	std::unordered_set<int> p_union_x = set_union(p, x);
	for (const int &w : p_union_x) {
		int size = _neighborhoods[w].size();
		if (size > max_size) {
			max_size = size;
			u = w;
		}
	}
	
	std::cout << indentation(depth);
	std::cout << "selected pivot u = " << u << "\n";
	
	std::unordered_set<int> search_area = set_difference(p, _neighborhoods[u]);
	
	std::cout << indentation(depth);
	std::cout << "search area: " << search_area << "\n";
	
	auto it = search_area.begin();
	while (it != search_area.end()) {
		int v = *it;
		
		std::cout << indentation(depth);
		std::cout << "v = " << v << ":\n";
		
		std::unordered_set<int> new_r = r;
		new_r.insert(v);
		std::unordered_set<int> new_p = set_intersection(p, _neighborhoods[v]);
		std::unordered_set<int> new_x = set_intersection(x, _neighborhoods[v]);
		
		bron_kerbosch_2(new_r, new_p, new_x, depth + 1);
		
		p.erase(v);
		it = search_area.erase(it);
		x.insert(v);
	}
	
	std::cout << indentation(depth) << "STOP\n";
}

void Graph::bron_kerbosch_3() const {
	std::unordered_set<int> r = {};
	std::unordered_set<int> p = _vertices;
	std::unordered_set<int> x = {};
	
	std::cout << indentation(0);
	std::cout << "R = " << r << ", P = " << p << ", X = " << x << "\n";
	
	auto degeneracy_ordering = this->degeneracy_ordering();
	
	std::cout << "degeneracy_ordering: ";
	for (int v : degeneracy_ordering) {
		std::cout << v << " ";
	}
	std::cout << "\n";
	
	for (auto v : degeneracy_ordering) {
		std::cout << "v = " << v << "\n";
	
		std::unordered_set<int> new_r = {v};
		std::unordered_set<int> new_p = set_intersection(p, _neighborhoods[v]);
		std::unordered_set<int> new_x = set_intersection(x, _neighborhoods[v]);
		bron_kerbosch_2(new_r, new_p, new_x, 1);
		
		p.erase(v);
		x.insert(v);
	}
	
	std::cout << "STOP\n";
}

void Graph::perform_algorithm() const {
	std::unordered_set<int> r = {};
	std::unordered_set<int> p = _vertices;
	std::unordered_set<int> x = {};

	// bron_kerbosch(r, p, x);
	// bron_kerbosch_2(r, p, x, 0);
	bron_kerbosch_3();
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

void Graph::print_found_clique(const std::unordered_set<int> &clique, const int &tab_depth) {
	std::cout << indentation(tab_depth) << clique << "\n";
}

std::string indentation(const int &depth) {
	std::stringstream buffer;

	for (int i = 0; i < depth; i++) {
		buffer << "|\t";
	}
	
	return buffer.str();
}

void print_to_console(const std::string &message, const int &tab_depth) {
	std::cout << indentation(tab_depth) << message << "\n";
}
