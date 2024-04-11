#include <iostream>
#include <fstream>

#include "test.hpp"
#include "graph.hpp"
#include "solve.hpp"

void test_graph(const std::string &graph_dir_name) {
	std::string input_filename = graph_dir_name + "/matrix.txt";
	std::string output_filename = graph_dir_name + "/results.txt";

	Graph g(input_filename);

	std::ofstream output_file(output_filename);
	if (!output_file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + output_filename);
	}
	
	perform_algorithm(g, AlgType::BASIC);
	perform_algorithm(g, AlgType::PIVOTING);
	perform_algorithm(g, AlgType::DEGEN_ORDERING);
}
