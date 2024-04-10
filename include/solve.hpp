#pragma once

#include <unordered_set>

#include "graph.hpp"

#define LOG

enum class AlgType {
	BASIC,
	PIVOTING,
	DEGEN_ORDERING
};

using set = std::unordered_set<int>;

void perform_algorithm(const Graph&, const AlgType&);
void bron_kerbosch_basic(const Graph&, const set&, set&, set&);
void bron_kerbosch_pivot(const Graph&, const set&, set&, set&, const int&);
void bron_kerbosch_degen(const Graph&);
