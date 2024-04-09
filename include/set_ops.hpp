#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <unordered_set>

// TODO: remove var names

std::unordered_set<int> set_union(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2);

std::unordered_set<int> set_intersection(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2);

std::unordered_set<int> set_difference(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2);

std::string set_to_string(const std::unordered_set<int>&);

std::ostream& operator << (std::ostream &out, const std::unordered_set<int> &set);

#endif
