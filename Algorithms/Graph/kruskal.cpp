#include <iostream>
#include <vector>
#include <algorithm>


struct edge
{
    size_t  from;
    size_t  to;
    int64_t weight;
};

class distinct_sets
{
private:
    std::vector<size_t> m_link;
    std::vector<size_t> m_size;
public:
    distinct_sets(size_t size)
    {
        for (size_t i = 0; i < size; ++i) {
            m_link.push_back(i);
            m_size.push_back(1);
        }
    }

    size_t find_repr(size_t vert)
    {
        while (vert != m_link[vert])
        {
            vert = m_link[vert];
        }
        return vert;
    }

    bool same_set(size_t lhs, size_t rhs)
    {
        return find_repr(lhs) == find_repr(rhs);
    }

    void unite_sets(size_t lhs, size_t rhs)
    {
        if (!same_set(lhs, rhs)) {
            lhs = find_repr(lhs);
            rhs = find_repr(rhs);
            if (m_size[lhs] < m_size[rhs]) {
                std::swap(lhs, rhs);
            }
            m_size[lhs] += m_size[rhs];
            m_link[rhs] = lhs;
        }
    }

};

std::vector<edge> kruskal(std::vector<edge>& graph) 
{
    std::vector<edge> min_tree;
    distinct_sets     set {graph.size()};

    std::sort(graph.begin(), graph.end(), 
            [](edge& lhs, edge& rhs){ return lhs.weight > rhs.weight; });

    for (auto& e : graph) 
    {
        if (!set.same_set(e.from, e.to)) {
            min_tree.push_back(e);
            set.unite_sets(e.from, e.to);
        }
    }
    
    return min_tree;
}


int main() 
{
    std::vector<edge> edges;
    return 0;
}