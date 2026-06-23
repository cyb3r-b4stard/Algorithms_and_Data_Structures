#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

struct Edge
{
    size_t from;
    size_t to;
    int64_t weight;
};

class DSU
{
public:
    DSU(size_t size)
        : m_size(size, 1), m_link(size)
    {
        std::iota(m_link.begin(), m_link.end(), 0);
    }
    
    size_t find_repr(size_t vertex)
    {
        if (vertex == m_link[vertex])
        {
            return vertex;
        }
        
        return m_link[vertex] = find_repr(m_link[vertex]);
    }
    
    bool same_set(size_t lhs, size_t rhs)
    {
        return find_repr(lhs) == find_repr(rhs);
    }
    
    void unite_sets(size_t lhs, size_t rhs)
    {
        if (!same_set(lhs, rhs))
        {
            lhs = find_repr(lhs);
            rhs = find_repr(rhs);
            
            if (m_size[lhs] < m_size[rhs])
            {
                std::swap(lhs, rhs);
            }
            m_size[lhs] += m_size[rhs];
            m_link[rhs] = lhs;
        }
    }
private:
    std::vector<size_t> m_link;
    std::vector<size_t> m_size;
};

/**
 * @brief Builds minimum-spanning-tree of weighted undirected connected graph
 *
 * @complexity O(E * log(E))
 */
std::vector<Edge> kruskal(std::vector<Edge> &graph)
{
    std::vector<Edge> min_tree;
    DSU set{graph.size()};

    std::sort(
        graph.begin(), graph.end(), 
        [](const Edge &lhs, const Edge &rhs)
        { 
            return lhs.weight < rhs.weight; 
        }
    );

    for (auto &e : graph)
    {
        if (!set.same_set(e.from, e.to))
        {
            min_tree.push_back(e);
            set.unite_sets(e.from, e.to);
        }
    }

    return min_tree;
}

int main()
{
    std::vector<Edge> edges;
    edges.push_back({0, 1, 5});
    edges.push_back({0, 2, 9});
    edges.push_back({0, 3, 1});
    edges.push_back({1, 2, 2});
    edges.push_back({2, 3, 2});

    auto min_tree = kruskal(edges);

    for (auto &x : min_tree)
    {
        std::cout << x.weight << ' ';
    }
    return 0;
}
