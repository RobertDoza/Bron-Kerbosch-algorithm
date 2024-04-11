#include <iostream>

#include "test.hpp"

/* TODO
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
		return 1;
	}

	std::string directory_path = argv[1];
	
	try {
		// test_graph(directory_path);
		test_graph("assets/blue_graph");
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
*/

int main() {
	try {
		test_graph("assets/blue_graph");
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
