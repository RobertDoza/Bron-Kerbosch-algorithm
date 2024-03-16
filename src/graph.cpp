#include <iostream>
#include <sstream>

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

void Graph::perform_algorithm() const {
	std::unordered_set<int> r = {};
	std::unordered_set<int> p = _vertices;
	std::unordered_set<int> x = {};

	// bron_kerbosch(r, p, x);
	bron_kerbosch_2(r, p, x, 0);
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
