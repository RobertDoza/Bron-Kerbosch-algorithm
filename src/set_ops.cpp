#include <iostream>
#include <sstream>

#include "set_ops.hpp"

set set_union(const set &s1, const set &s2) {
	set result(s1);
	
	result.insert(s2.begin(), s2.end());
	
	return result;
}

set set_intersection(const set &s1, const set &s2) {
	set result;
	
	for (const int &element : s1) {
		if (s2.count(element) > 0) {
			result.insert(element);
		}
	}
	
	return result;
}

set set_difference(const set &s1, const set &s2) {
	set result(s1);
	
	for (const int &element : s2) {
			result.erase(element);
	}
	
	return result;
}

std::string set_to_string(const set &s) {
	if (s.empty()) {
		return "{}";
	}
	
	std::stringstream buffer;
	
	buffer << "{";
	
	unsigned i = 1;
	for (const int &element : s) {
		buffer << element;
		if (i != s.size()) {
			buffer << ", ";
		}
		i++;
	}
	
	buffer << "}";
	
	return buffer.str();
}

std::ostream& operator << (std::ostream &out, const set &s) {
	out << set_to_string(s);
	
	return out;
}
