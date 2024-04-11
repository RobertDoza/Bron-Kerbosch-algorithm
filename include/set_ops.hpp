#pragma once

#include <unordered_set>

using set = std::unordered_set<int>;

// Function calculates the union of two sets.
set set_union(const set&, const set&);

// Function calculates the intersection of two sets.
set set_intersection(const set&, const set&);

// Function calculates the difference of two sets.
set set_difference(const set&, const set&);

// Function calculates the string representation of a given set.
std::string set_to_string(const set&);

// Operator << overload writes the string representation of the set to the output stream.
std::ostream& operator << (std::ostream &out, const set&);
