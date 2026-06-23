#include <iostream>
#include <vector>
#include <cstdint>

const int64_t INF{INT64_MAX};

struct Edge
{
    size_t from;
    size_t to;
    int64_t weight;
};

/**
 * @brief Calculates minimal distance between given vertices in a
 *        weighted graph. Can be applied to any weighted graph containing
 *        no cycles of negative weight.
 *
 * @complexity O(VE)
 */
int64_t bellman_ford(const std::vector<Edge> &graph, size_t vertices_count, size_t start, size_t finish)
{
    std::vector<int64_t> dist(vertices_count, INF);

    dist[start] = 0;

    for (size_t i{1}; i < vertices_count; ++i)
    {
        for (auto &e : graph)
        {
            dist[e.to] = std::min(dist[e.to], dist[e.from] + e.weight);
        }
    }
    /**
     * Additional iteration over edges can be used to detect cycles of negative weight
     */
    for (auto &e : graph)
    {
        /**
         * Distance can be made smaller, hence there is a cycle of negative weight
         */
        if (dist[e.to] < dist[e.from] + e.weight)
        {
            return -1;
        }
    }

    return dist[finish];
}

int main()
{
    std::vector<Edge> graph{
        {0, 1, 5}, {0, 3, 9}, {0, 4, 1}, {1, 0, 5}, {1, 2, 2}, {2, 1, 2}, {2, 3, 6}, {3, 0, 9}, {3, 2, 6}, {3, 4, 2}, {4, 0, 1}, {4, 3, 2}};

    std::cout << bellman_ford(graph, 5, 0, 1) << std::endl;
}
