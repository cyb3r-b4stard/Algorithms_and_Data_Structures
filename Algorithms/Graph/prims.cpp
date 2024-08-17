#include <iostream>
#include <vector>
#include <list>
#include <queue>

/**
 * @brief Builds minimum-spanning-tree of weighted undirected connected graph
 * 
 * @complexity O(V + E * log(E))
 */

struct edge {
    size_t  from;
    size_t  to;
    int64_t weight;
};

struct compare {
    bool operator() (const edge& lhs, const edge& rhs)
    {
        return lhs.weight > rhs.weight;
    }
};

std::vector<edge> prims(std::vector<std::list<std::pair<size_t, int64_t>>>& graph)
{
    std::priority_queue<edge, std::vector<edge>, compare> queue;
    std::vector<edge> min_tree;
    std::vector<bool> taken (graph.size(), false);
    edge current;

    taken[0] = true;

    for (auto& e : graph[0]) {
        queue.push({0, e.first, e.second});
    }

    for (size_t i = 1; i < graph.size(); ++i) {
        current = queue.top();
        queue.pop();

        for (auto& e : graph[current.to]) {
            if (!taken[e.first]) {
                queue.push( {current.to, e.first, e.second} );
            }
        }
        
        taken[current.to] = true;
        min_tree.push_back(current);
    }

    return min_tree;
}

int main() {
    
    return 0;
}
