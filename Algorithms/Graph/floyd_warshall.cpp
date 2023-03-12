#include <iostream>
#include <vector>

#define inf 1e9

int64_t floyd_warshall(std::vector<std::vector<int64_t>>& graph, size_t start, size_t finish) 
{
    std::vector<std::vector<int64_t>> dist (graph.size(), std::vector<int64_t> (graph.size());
    int64_t                           value;

    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph.size(); ++j) {
            if (i == j) {
                value = 0;
            } else if (graph[i][j]) {
                value = graph[i][j];
            } else {
                value = inf;
            }
            dist[i][j] = value;
        }
    }

    for (size_t k = 0; k < graph.size(); ++k) {
        for (size_t i = 0; i < graph.size(); ++i) {
            for (size_t j = 0; j < graph.size(); ++j) {
                dist[i][j] = std::min(dist[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    return dist[start][finish];
}


int main() 
{            
    std::vector<std::vector<int64_t>> graph { 
                                                {0, 5, 0, 9, 1},
                                                {5, 0, 2, 0, 0},
                                                {0, 2, 0, 6, 0},
                                                {9, 0, 6, 0, 2},
                                                {1, 0, 0, 2, 0}
                                            };
    std::cout << floyd_warshall(graph, 0, 1) << std::endl;
}
