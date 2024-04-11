#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_set>
#include <ostream>

class Graph {
	public:
		Graph(const std::string&);
		Graph(const std::vector<std::pair<int, int>>&);
		
		std::vector<int> degeneracy_ordering() const;
		
		std::unordered_set<int> get_vertices() const;
		std::unordered_set<int> get_neighborhood(int) const;
		
		friend std::ostream& operator << (std::ostream&, const Graph&);
	private:
		std::unordered_set<int> _vertices;
		std::vector<std::unordered_set<int>> _neighborhoods;
		
		static std::unordered_set<int> calculate_vertices(const std::vector<std::pair<int, int>>&);
};

#endif
