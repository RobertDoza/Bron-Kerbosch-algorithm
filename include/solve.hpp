#pragma once

#include <unordered_set>

#include "graph.hpp"

enum class AlgType {
	BASIC,
	PIVOTING,
	DEGEN_ORDERING
};

using set = std::unordered_set<int>;

// Function performs the Bron-Kerbosch algorithm on the specified graph, using the specified algorithm variant.
unsigned perform_algorithm(const Graph&, const AlgType&);

// Function performs the basic version of the Bron-Kerbosch algorithm on the specified graph, using the provided sets.
unsigned bron_kerbosch_basic(const Graph&, const set&, set&, set&, const int&);

// Function performs the pivoted version of the Bron-Kerbosch algorithm on the specified graph, using the provided sets.
unsigned bron_kerbosch_pivot(const Graph&, const set&, set&, set&, const int&);

// Function performs the degeneracy ordering version of the Bron-Kerbosch algorithm on the specified graph, using the provided sets.
unsigned bron_kerbosch_degen(const Graph&);

// Function calculates the degeneracy ordering of the graph.
std::vector<int> degeneracy_ordering(const Graph&);
