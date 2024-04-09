#include <iostream>

#include "set_ops.hpp"

std::unordered_set<int> set_union(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2) {
	std::unordered_set<int> result(set1);
	
	result.insert(set2.begin(), set2.end());
	
	return result;
}

std::unordered_set<int> set_intersection(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2) {
	std::unordered_set<int> result;
	
	for (const int &element : set1) {
		if (set2.count(element) > 0) {
			result.insert(element);
		}
	}
	
	return result;
}

std::unordered_set<int> set_difference(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2) {
	std::unordered_set<int> result(set1);
	
	for (const int &element : set2) {
			result.erase(element);
	}
	
	return result;
}

std::ostream& operator << (std::ostream &out, const std::unordered_set<int> &set) {
	if (set.empty()) {
		out << "{}";
		return out;
	}
	
	out << "{";

	for (const int &element : set) {
		out << element << ", ";
	}
	out << "\b\b}";
	
	return out;
}
