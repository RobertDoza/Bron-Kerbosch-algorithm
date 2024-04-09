#include "solve.hpp"
#include "logger.hpp"
#include "set_ops.hpp"

void bron_kerbosch_basic(const Graph &g, const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x) {
	if (p.empty() && x.empty()) {
		// TODO
		Logger::log(set_to_string(r));
		// std::cout << r << "\n";
		return;
	}
	
	auto it = p.begin();
	while (it != p.end()) {
		int v = *it;
		
		std::unordered_set<int> new_r = r;
		new_r.insert(v);
		std::unordered_set<int> new_p = set_intersection(p, g.get_neighborhood(v));
		std::unordered_set<int> new_x = set_intersection(x, g.get_neighborhood(v));
		
		bron_kerbosch_basic(g, new_r, new_p, new_x);
		
		it = p.erase(it);
		x.insert(v);
	}
}

/*
void Graph::bron_kerbosch_2(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x, const int &depth) const {
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x), depth);

	if (p.empty() && x.empty()) {
		Logger::log("found clique: " + set_to_string(r), depth);
		Logger::log("STOP", depth);
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
	
	Logger::log("selected pivot u = " + std::to_string(u), depth);
	
	std::unordered_set<int> search_area = set_difference(p, _neighborhoods[u]);
	
	Logger::log("search area: " + set_to_string(search_area), depth);
	
	auto it = search_area.begin();
	while (it != search_area.end()) {
		int v = *it;
		
		Logger::log("v = " + std::to_string(v) + ":", depth);
		
		std::unordered_set<int> new_r = r;
		new_r.insert(v);
		std::unordered_set<int> new_p = set_intersection(p, _neighborhoods[v]);
		std::unordered_set<int> new_x = set_intersection(x, _neighborhoods[v]);
		
		bron_kerbosch_2(new_r, new_p, new_x, depth + 1);
		
		p.erase(v);
		it = search_area.erase(it);
		x.insert(v);
	}
	
	Logger::log("STOP", depth);
}

void Graph::bron_kerbosch_3() const {
	std::unordered_set<int> r = {};
	std::unordered_set<int> p = _vertices;
	std::unordered_set<int> x = {};
	
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x));
	
	auto degeneracy_ordering = this->degeneracy_ordering();
	
	std::stringstream buffer;
	buffer << "degeneracy ordering: ";
	for (int v : degeneracy_ordering) {
		buffer << v << " ";
	}
	Logger::log(buffer.str());
	
	for (auto v : degeneracy_ordering) {
		Logger::log("v = " + std::to_string(v));
	
		std::unordered_set<int> new_r = {v};
		std::unordered_set<int> new_p = set_intersection(p, _neighborhoods[v]);
		std::unordered_set<int> new_x = set_intersection(x, _neighborhoods[v]);
		bron_kerbosch_2(new_r, new_p, new_x, 1);
		
		p.erase(v);
		x.insert(v);
	}
	
	Logger::log("STOP");
}
*/

void perform_algorithm(const Graph &g, const AlgType &algorithm) {
	if (algorithm == AlgType::BASIC) {
		std::unordered_set<int> r = {};
		std::unordered_set<int> p = g.get_vertices();
		std::unordered_set<int> x = {};
		bron_kerbosch_basic(g, r, p, x);
	} else if (algorithm == AlgType::PIVOTING) {
		/*
		std::unordered_set<int> r = {};
		std::unordered_set<int> p = _vertices;
		std::unordered_set<int> x = {};
		bron_kerbosch(r, p, x);
		bron_kerbosch_2(r, p, x, 0);
		*/
	} else if (algorithm == AlgType::DEGEN_ORDERING) {
		// bron_kerbosch_3();
	} else {
		// TODO: error
	}
}
