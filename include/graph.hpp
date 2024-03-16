#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_set>
#include <ostream>

class Graph {
	public:
		Graph(const std::vector<std::pair<int, int>> &edges);
		Graph(const std::string &filename);
		
		void perform_algorithm() const;
		
		std::vector<int> degeneracy_ordering() const;
		
		friend std::ostream& operator << (std::ostream &out, const Graph &g);
	private:
		std::unordered_set<int> _vertices;
		std::vector<std::unordered_set<int>> _neighborhoods;
		
		static std::unordered_set<int> calculate_vertices(const std::vector<std::pair<int, int>> &edges);
		static void print_found_clique(const std::unordered_set<int> &clique, const int &tab_depth);
		
		void bron_kerbosch(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x) const;
		void bron_kerbosch_2(const std::unordered_set<int> &r, std::unordered_set<int> &p, std::unordered_set<int> &x, const int &depth) const;
};

std::string indentation(const int &depth);
void print_to_console(const std::string &message, const int &tab_depth);

#endif
