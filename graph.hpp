#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_set>
#include <ostream>

class Graph {
	public:
		Graph(const std::vector<std::pair<int, int>> &edges);
		
		void perform_algorithm() const;
		
		friend std::ostream& operator << (std::ostream &out, const Graph &g);
	private:
		std::unordered_set<int> _vertices;
		std::vector<std::unordered_set<int>> _neighborhoods;
		
		static std::unordered_set<int> calculate_vertices(const std::vector<std::pair<int, int>> &edges);
		void algorithm(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x) const;
};

#endif
