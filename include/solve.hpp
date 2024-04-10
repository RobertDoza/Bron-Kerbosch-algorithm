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
unsigned bron_kerbosch_basic(const Graph&, const set&, set&, set&);
unsigned bron_kerbosch_pivot(const Graph&, const set&, set&, set&, const int&);
unsigned bron_kerbosch_degen(const Graph&);
