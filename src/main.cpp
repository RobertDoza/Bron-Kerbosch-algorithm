#include <iostream>

#include "test.hpp"

int main() {
	try {
		test_graph("assets/blue_graph");
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
