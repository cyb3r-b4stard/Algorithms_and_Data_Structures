#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <cstdint>

const int64_t INF{INT64_MAX};

enum class Status
{
    UNPROCESSED,
    PROCESSING,
    PROCESSED
};

struct Vertex
{
    Status status{Status::UNPROCESSED};
    int64_t id;
    
    Vertex(int64_t _id)
        : id(_id)
    {}
};

void dfs_visit(std::vector<std::vector<int64_t>> &graph, std::vector<Vertex> &vertices, std::vector<int64_t> &sorted, int64_t start_id)
{
    std::stack<int64_t> stack;
    int64_t current;
    
    stack.push(start_id);
    
    while (!stack.empty())
    {
        current = stack.top();
        for (auto &next : graph[current])
        {
            if (vertices[next].status == Status::PROCESSING)
            {
                throw std::logic_error("The graph is not acyclic!");
            }
            else if (vertices[next].status == Status::UNPROCESSED)
            {
                stack.push(next);
            }
        }
        
        if (stack.top() == current)
        {
            vertices[current].status = Status::PROCESSED;
            sorted.push_back(current);
            stack.pop();
        }
    }
}

/**
 * @brief Performs a topology sort on any directed acyclic graph, the resulting
 *        order obeys the following condition:
 *        if there is a path a_i -> a_j, then i < j
 *
 * @complexity O(V + E)
 */
std::vector<int64_t> topology_sort(std::vector<std::vector<int64_t>> &graph, std::vector<Vertex> &vertices)
{
    std::vector<int64_t> sorted;
    
    for (auto &vertex : vertices)
    {
        if (vertex.status == Status::UNPROCESSED)
        {
            dfs_visit(graph, vertices, sorted, vertex.id);
        }
    }
    std::reverse(sorted.begin(), sorted.end());
    
    return sorted;
}

int main()
{
    std::vector<std::vector<int64_t>> graph(7);
    std::vector<Vertex> vertices;
    std::vector<int64_t> sorted;
    int a, b;

    for (int i{0}; i < 6; ++i)
        vertices.push_back(Vertex(i));
    for (int i{0}; i < 7; ++i)
    {
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    sorted = topology_sort(graph, vertices);

    for (auto &x : sorted)
    {
        std::cout << x << ' ';
    }

    std::cout << std::endl;
}
