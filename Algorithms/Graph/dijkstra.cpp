#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <list>

/**
 * @brief Calculates minimal distance between given vertices in any graph
 *        with no edges of negative weight.
 * 
 * @complexity O(V + E * log(E))
 */

const int64_t inf {INT64_MAX};

int64_t dijkstra(const std::vector<std::list<std::pair<size_t, int64_t>>>& graph, size_t start, size_t finish) {
    std::priority_queue<std::pair<size_t, int64_t>> queue;
    std::pair<size_t, int64_t>                      current;
    std::vector<int64_t>                            dist(graph.size(), inf);

    queue.push({start, 0});
    dist[start] = 0;

    while (!queue.empty()) {
        current = queue.top();
        queue.pop();

        if (dist[current.first] < -current.second) continue;

        for (auto& [index, weight] : graph[current.first]) {
            if (dist[index] > -current.second + weight) {
                dist[index] = -current.second + weight;
                queue.push({index, -dist[index]});
            }
        }
    }

    return dist[finish];
}

int main() 
{
    std::vector<std::list<std::pair<size_t, int64_t>>> graph;
    graph.push_back( { {1, 5}, {3, 9}, {4, 1} } );
    graph.push_back( { {0, 5}, {2, 2} } );
    graph.push_back( { {1, 2}, {3, 6} } );
    graph.push_back( { {0, 9}, {2, 6}, {4, 2} } );
    graph.push_back( { {0, 1}, {3, 2} } );

    std::cout << dijkstra(graph, 0, 1) << std::endl;                                        
}