#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <unordered_set>

using set = std::unordered_set<int>;

set set_union(const set&, const set&);

set set_intersection(const set&, const set&);

set set_difference(const set&, const set&);

std::string set_to_string(const set&);

std::ostream& operator << (std::ostream &out, const set&);

#endif
