#include <iostream>
#include <fstream>

#include "test.hpp"
#include "graph.hpp"
#include "solve.hpp"
#include "logger.hpp"

void test_graph(const std::string &graph_dir_name) {
	std::string input_filename = graph_dir_name + "/matrix.txt";
	std::string output_filename = graph_dir_name + "/results.txt";

	Graph g(input_filename);

	std::ofstream output_file(output_filename);
	if (!output_file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + output_filename);
	}
	
	AlgResult result;
	
	result = perform_algorithm(g, AlgType::BASIC);
	unsigned num_calls_basic = result.num_function_calls;
	double time_basic = result.time;
	
	#ifdef LOG
	Logger::log("");
	#endif
	
	result = perform_algorithm(g, AlgType::PIVOTING);
	unsigned num_calls_pivot = result.num_function_calls;
	double time_pivot = result.time;
	
	#ifdef LOG
	Logger::log("");
	#endif
	
	result = perform_algorithm(g, AlgType::DEGEN_ORDERING);
	unsigned num_calls_degen = result.num_function_calls;
	double time_degen = result.time;
	
	output_file << "Number of function calls:\n";
	output_file << "basic: " << std::to_string(num_calls_basic) << "\n";
	output_file << "pivot: " << std::to_string(num_calls_pivot) << "\n";
	output_file << "degen: " << std::to_string(num_calls_degen) << "\n";
	
	output_file << "\n";
	
	output_file << "Time:\n";
	output_file << "basic: " << std::to_string(time_basic) << "s\n";
	output_file << "pivot: " << std::to_string(time_pivot) << "s\n";
	output_file << "degen: " << std::to_string(time_degen) << "s\n";
}
