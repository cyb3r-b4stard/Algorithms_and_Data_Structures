#include <iostream>
#include <vector>

struct edge 
{
    size_t from;
    size_t to;
    int64_t weight;
};

int64_t bellman_ford(const std::vector<edge>& graph, size_t gSize, size_t start, size_t finish)
{
    std::vector<int64_t> dist;

    for (size_t i = 0; i < gSize; ++i) {
        dist.push_back(INT64_MAX);
    }

    dist[start] = 0;

    for (size_t i = 2; i <= gSize; ++i) {
        for (auto& e : graph) {
            dist[e.to] = std::min(dist[e.to], dist[e.from] + e.weight);
        }
    }

    return dist[finish];
}

int main() 
{
    std::vector<edge> graph {
                              {0, 1, 5}, {0, 3, 9}, {0, 4, 1},
                              {1, 0, 5}, {1, 2, 2}, {2, 1, 2}, 
                              {2, 3, 6}, {3, 0, 9}, {3, 2, 6}, 
                              {3, 4, 2}, {4, 0, 1}, {4, 3, 2}
                            };

    std::cout << bellman_ford(graph, 5, 0, 1) << std::endl;                                        
}