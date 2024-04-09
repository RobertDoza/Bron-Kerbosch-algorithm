#pragma once

#include <unordered_set>

#include "graph.hpp"

enum class AlgType {
	BASIC,
	PIVOTING,
	DEGEN_ORDERING
};

using set = std::unordered_set<int>;

// TODO
void perform_algorithm(const Graph&, const AlgType&);
void bron_kerbosch_basic(const Graph&, const set &r, set &p, set &x);
void bron_kerbosch_pivot(const Graph&, const set &r, set &p, set &x, const int &depth);
void bron_kerbosch_degen(const Graph&);
