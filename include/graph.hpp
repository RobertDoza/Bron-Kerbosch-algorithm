#pragma once

#include <vector>
#include <unordered_set>
#include <ostream>

class Graph {
	public:
		// Constructor creates a graph using the adjacency matrix in a file. The file is located on a path given by string argument.
		Graph(const std::string&);
		
		// Constructor creates a graph using an array of edges.
		Graph(const std::vector<std::pair<int, int>>&);
		
		// Getter returns the vertices of the graph.
		std::unordered_set<int> get_vertices() const;
		
		// Getter returns the neighboring vertices of the vertex passed as the function argument.
		std::unordered_set<int> get_neighborhood(int) const;
		
		// Operator << overload writes the string representation of the graph to the output stream.
		friend std::ostream& operator << (std::ostream&, const Graph&);
	private:
		// Class members
		std::unordered_set<int> _vertices;
		std::vector<std::unordered_set<int>> _neighborhoods;
		
		// Function calculates the vertices that appear in the graph using the provided array of edges.
		static std::unordered_set<int> calculate_vertices(const std::vector<std::pair<int, int>>&);
};
