#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <cstdint>

const int64_t INF{INT64_MAX};

enum class Status
{
    UNPROCESSED, PROCESSING, PROCESSED
};

struct Vertex
{
    int64_t distance{INF};
    int64_t parent{-1};
    int64_t id;
    
    Status status{Status::UNPROCESSED};
    
    Vertex(int64_t t_id)
    : id(t_id) 
    {}
};

/**
 * @brief Performs breadth-first-search on an undirected graph
 *
 * @complexity O(V + E)
 */
void bfs(std::vector<std::list<int64_t>> &graph, std::vector<Vertex> &vertices, int64_t start)
{
    std::queue<int64_t> q;
    int64_t current;

    vertices[start].status = Status::PROCESSING;
    vertices[start].distance = 0;
    q.push(start);

    while (!q.empty())
    {
        current = q.front();
        q.pop();

        for (auto &x : graph[current])
        {
            if (vertices[x].status == Status::UNPROCESSED)
            {
                vertices[x].status = Status::PROCESSING;
                vertices[x].distance = vertices[current].distance + 1;
                vertices[x].parent = current;
                q.push(x);
            }
        }
        vertices[current].status = Status::PROCESSED;
    }
}

int main()
{
    std::vector<std::list<int64_t>> graph(4);
    std::vector<Vertex> vertices;
    int a, b;

    for (int64_t i{0}; i < graph.size(); ++i)
    {
        vertices.push_back(Vertex(i));
    }

    for (size_t i{0}; i < 4; ++i)
    {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs(graph, vertices, 0);
}