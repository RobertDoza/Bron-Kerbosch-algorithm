#include <iostream>

#include "test.hpp"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
		return 1;
	}

	std::string directory_path = argv[1];
	
	try {
		test_graph(directory_path);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
