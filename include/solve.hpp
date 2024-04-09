#pragma once

#include <unordered_set>

#include "graph.hpp"

enum class AlgType {
	BASIC,
	PIVOTING,
	DEGEN_ORDERING
};

// TODO
void perform_algorithm(const Graph&, const AlgType&);
void bron_kerbosch_basic(const Graph&, const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x);
void bron_kerbosch_pivot(const Graph&, const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x, const int &depth);
void bron_kerbosch_degen(const Graph&);
