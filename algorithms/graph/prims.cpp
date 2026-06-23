#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct Edge
{
    size_t from;
    size_t to;
    int64_t weight;
};

struct Comparator
{
    bool operator()(const Edge &lhs, const Edge &rhs)
    {
        return lhs.weight > rhs.weight;
    }
};

/**
 * @brief Builds minimum-spanning-tree of weighted undirected connected graph
 *
 * @complexity O(V + E * log(E))
 */
std::vector<Edge> prims(std::vector<std::list<std::pair<size_t, int64_t>>> &graph)
{
    std::priority_queue<Edge, std::vector<Edge>, Comparator> queue;
    std::vector<Edge> min_tree;
    std::vector<bool> taken(graph.size(), false);
    Edge current;

    taken[0] = true;

    for (auto &e : graph[0])
    {
        queue.push({0, e.first, e.second});
    }

    for (size_t i{1}; i < graph.size(); ++i)
    {
        current = queue.top();
        queue.pop();

        for (auto &e : graph[current.to])
        {
            if (!taken[e.first])
            {
                queue.push({current.to, e.first, e.second});
            }
        }

        taken[current.to] = true;
        min_tree.push_back(current);
    }

    return min_tree;
}

int main()
{
    return 0;
}
