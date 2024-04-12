#include <sstream>
#include <algorithm>
#include <chrono>

#include "solve.hpp"
#include "logger.hpp"
#include "set_ops.hpp"

unsigned bron_kerbosch_basic(const Graph &g, const set &r, set &p, set &x, const int &depth) {
	unsigned num_function_calls = 1;
	
	#ifdef LOG
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x), depth);
	#endif

	if (p.empty() && x.empty()) {
		#ifdef LOG
		Logger::log("found clique: " + set_to_string(r), depth);
		Logger::log("STOP", depth);
		#endif
		return num_function_calls;
	}
	
	auto it = p.begin();
	while (it != p.end()) {
		int v = *it;
		
		#ifdef LOG
		Logger::log("v = " + std::to_string(v) + ":", depth);
		#endif
		
		set new_r = r;
		new_r.insert(v);
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		
		num_function_calls += bron_kerbosch_basic(g, new_r, new_p, new_x, depth + 1);
		
		it = p.erase(it);
		x.insert(v);
	}
	
	#ifdef LOG
	Logger::log("STOP", depth);
	#endif
	
	return num_function_calls;
}

unsigned bron_kerbosch_pivot(const Graph &g, const set &r, set &p, set &x, const int &depth) {
	unsigned num_function_calls = 1;

	#ifdef LOG
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x), depth);
	#endif

	if (p.empty() && x.empty()) {
		#ifdef LOG
		Logger::log("found clique: " + set_to_string(r), depth);
		Logger::log("STOP", depth);
		#endif
		return num_function_calls;
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
	
	#ifdef LOG
	Logger::log("selected pivot u = " + std::to_string(u), depth);
	#endif
	
	set search_area = set_difference(p, g.get_neighborhood(u));
	
	#ifdef LOG
	Logger::log("search area: " + set_to_string(search_area), depth);
	#endif
	
	auto it = search_area.begin();
	while (it != search_area.end()) {
		int v = *it;
		
		#ifdef LOG
		Logger::log("v = " + std::to_string(v) + ":", depth);
		#endif
		
		set new_r = r;
		new_r.insert(v);
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		
		num_function_calls += bron_kerbosch_pivot(g, new_r, new_p, new_x, depth + 1);
		
		p.erase(v);
		it = search_area.erase(it);
		x.insert(v);
	}
	
	#ifdef LOG
	Logger::log("STOP", depth);
	#endif
	
	return num_function_calls;
}

unsigned bron_kerbosch_degen(const Graph &g) {
	unsigned num_function_calls = 1;

	set r = {};
	set p = g.get_vertices();
	set x = {};
	
	#ifdef LOG
	Logger::log("R = " + set_to_string(r) + ", P = " + set_to_string(p) + ", X = " + set_to_string(x));
	#endif
	
	auto degen_ordering = degeneracy_ordering(g);
	
	#ifdef LOG
	std::stringstream buffer;
	buffer << "degeneracy ordering: ";
	for (int v : degen_ordering) {
		buffer << v << " ";
	}
	Logger::log(buffer.str());
	#endif
	
	for (auto v : degen_ordering) {
		#ifdef LOG
		Logger::log("v = " + std::to_string(v));
		#endif
	
		set new_r = {v};
		set new_p = set_intersection(p, g.get_neighborhood(v));
		set new_x = set_intersection(x, g.get_neighborhood(v));
		
		num_function_calls += bron_kerbosch_pivot(g, new_r, new_p, new_x, 1);
		
		p.erase(v);
		x.insert(v);
	}
	
	#ifdef LOG
	Logger::log("STOP");
	#endif
	
	return num_function_calls;
}

std::vector<int> degeneracy_ordering(const Graph &g) {
	unsigned n = g.get_vertices().size();
	std::vector<int> l;
	std::vector<int> degrees(n);
	
	int max_degree = 0;
	for (const int v : g.get_vertices()) {
		degrees[v] = g.get_neighborhood(v).size();
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
		
		for (auto w : g.get_neighborhood(v)) {
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

unsigned perform_algorithm(const Graph &g, const AlgType &algorithm) {
	using clock = std::chrono::high_resolution_clock;
	
	clock::time_point start;
	clock::time_point end;

	if (algorithm == AlgType::BASIC) {	
		#ifdef LOG
		Logger::log("Bron-Kerbosch algorithm - BASIC\n");
		#endif
				
		set r = {};
		set p = g.get_vertices();
		set x = {};
		
		start = clock::now();
		
		unsigned num_function_calls = bron_kerbosch_basic(g, r, p, x, 0);
		
		end = clock::now();
		
		std::chrono::duration<double> elapsed = end - start;
		
		#ifdef LOG
		Logger::log("function calls: " + std::to_string(num_function_calls));
		Logger::log("time: " + std::to_string(elapsed.count()) + "s");
		#endif
		
		return num_function_calls;
	} else if (algorithm == AlgType::PIVOTING) {
		#ifdef LOG
		Logger::log("Bron-Kerbosch algorithm - WITH PIVOTING\n");
		#endif
	
		set r = {};
		set p = g.get_vertices();
		set x = {};
		
		start = clock::now();
		
		unsigned num_function_calls = bron_kerbosch_pivot(g, r, p, x, 0);
		
		end = clock::now();
		
		std::chrono::duration<double> elapsed = end - start;
		
		#ifdef LOG
		Logger::log("function calls: " + std::to_string(num_function_calls));
		Logger::log("time: " + std::to_string(elapsed.count()) + "s");
		#endif
		
		return num_function_calls;
	} else if (algorithm == AlgType::DEGEN_ORDERING) {
		#ifdef LOG
		Logger::log("Bron-Kerbosch algorithm - WITH DEGENERACY ORDERING\n");
		#endif
		
		start = clock::now();
		
		unsigned num_function_calls = bron_kerbosch_degen(g);
		
		end = clock::now();
		
		std::chrono::duration<double> elapsed = end - start;
		
		#ifdef LOG
		Logger::log("function calls: " + std::to_string(num_function_calls));
		Logger::log("time: " + std::to_string(elapsed.count()) + "s");
		#endif
		
		return num_function_calls;
	} else {
		throw std::runtime_error("Error - unknown algorithm type!");
	}
}
