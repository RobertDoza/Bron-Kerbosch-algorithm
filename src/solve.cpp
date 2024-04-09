#include <sstream>

#include "solve.hpp"
#include "logger.hpp"
#include "set_ops.hpp"

void bron_kerbosch_basic(const Graph &g, const set &r, set &p, set &x) {
	if (p.empty() && x.empty()) {
		// TODO
		Logger::log(set_to_string(r));
		// std::cout << r << "\n";
		return;
	}
	
	auto it = p.begin();
	while (it != p.end()) {
		int v = *it;
		
		set new_r = r;
		new_r.insert(v);
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		
		bron_kerbosch_basic(g, new_r, new_p, new_x);
		
		it = p.erase(it);
		x.insert(v);
	}
}

void bron_kerbosch_pivot(const Graph &g, const set &r, set &p, set &x, const int &depth) {
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x), depth);

	if (p.empty() && x.empty()) {
		Logger::log("found clique: " + set_to_string(r), depth);
		Logger::log("STOP", depth);
		return;
	}
	
	int u = 0;
	int max_size = 0;
	set p_union_x = set_union(p, x);
	for (const int &w : p_union_x) {
		int size = g.get_neighborhood(w).size();
		if (size > max_size) {
			max_size = size;
			u = w;
		}
	}
	
	Logger::log("selected pivot u = " + std::to_string(u), depth);
	
	set search_area = set_difference(p, g.get_neighborhood(u));
	
	Logger::log("search area: " + set_to_string(search_area), depth);
	
	auto it = search_area.begin();
	while (it != search_area.end()) {
		int v = *it;
		
		Logger::log("v = " + std::to_string(v) + ":", depth);
		
		set new_r = r;
		new_r.insert(v);
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		
		bron_kerbosch_pivot(g, new_r, new_p, new_x, depth + 1);
		
		p.erase(v);
		it = search_area.erase(it);
		x.insert(v);
	}
	
	Logger::log("STOP", depth);
}

void bron_kerbosch_degen(const Graph &g) {
	set r = {};
	set p = g.get_vertices();
	set x = {};
	
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x));
	
	auto degeneracy_ordering = g.degeneracy_ordering();
	
	std::stringstream buffer;
	buffer << "degeneracy ordering: ";
	for (int v : degeneracy_ordering) {
		buffer << v << " ";
	}
	Logger::log(buffer.str());
	
	for (auto v : degeneracy_ordering) {
		Logger::log("v = " + std::to_string(v));
	
		set new_r = {v};
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		bron_kerbosch_pivot(g, new_r, new_p, new_x, 1);
		
		p.erase(v);
		x.insert(v);
	}
	
	Logger::log("STOP");
}

void perform_algorithm(const Graph &g, const AlgType &algorithm) {
	if (algorithm == AlgType::BASIC) {
		set r = {};
		set p = g.get_vertices();
		set x = {};
		bron_kerbosch_basic(g, r, p, x);
	} else if (algorithm == AlgType::PIVOTING) {
		set r = {};
		set p = g.get_vertices();
		set x = {};
		bron_kerbosch_pivot(g, r, p, x, 0);
	} else if (algorithm == AlgType::DEGEN_ORDERING) {
		bron_kerbosch_degen(g);
	} else {
		// TODO: error
	}
}
