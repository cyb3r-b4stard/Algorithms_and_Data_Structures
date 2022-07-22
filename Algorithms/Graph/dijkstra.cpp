#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <list>

struct compare 
{
    typedef std::pair<int64_t, size_t> pair;

    bool operator() (const pair& lhs, const pair& rhs) 
    {
        return lhs.second < rhs.second;
    }
};

int64_t dijkstra(const std::vector<std::list<std::pair<size_t, int64_t>>>& graph, size_t start, size_t finish) 
{
    std::priority_queue<std::pair<size_t, int64_t>, std::vector<std::pair<size_t, int64_t>>, compare> queue;
    std::pair<size_t, int64_t>                      vCurrent;
    std::vector<int64_t>                            dist;
    std::vector<bool>                               processed;

    for (size_t i = 0; i < graph.size(); ++i) {
        dist.push_back(INT64_MAX);
        processed.push_back(false);
    }

    queue.push( {start, 0} );
    dist[start] = 0;

    while (!queue.empty()) {
        vCurrent = queue.top();
        queue.pop();

        if (processed[vCurrent.first]) continue;

        processed[vCurrent.first] = true;

        for (auto [index, weight] : graph[vCurrent.first]) {
            if (dist[index] > vCurrent.second + weight) {
                dist[index] = vCurrent.second + weight;
                queue.push( {index, dist[index]} );
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