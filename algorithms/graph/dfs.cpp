#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <stdexcept>


enum class Status
{
    UNPROCESSED,
    PROCESSING,
    PROCESSED
};

struct Vertex
{
    Status status{Status::UNPROCESSED};
    
    int64_t time_start{-1};
    int64_t time_finish{-1};
    int64_t parent{-1};
    int64_t connectivity_component{-1};
    int64_t id;
    
    Vertex(int64_t _id)
        : id(_id)
    {}
};

void dfs_visit(std::vector<std::vector<int64_t>> &graph, std::vector<Vertex> &vertices, int64_t start_id)
{
    int64_t counter{0}, current;
    std::stack<int64_t> stack;
    
    stack.push(start_id);
    
    while (!stack.empty())
    {
        current = stack.top();
        
        vertices[start_id].time_start = ++counter;
        vertices[current].status = Status::PROCESSING;
        
        for (auto &next : graph[current])
        {
            if (vertices[next].status == Status::UNPROCESSED)
            {
                vertices[next].parent = current;
                vertices[next].connectivity_component = vertices[current].connectivity_component;
                stack.push(next);
            }
            else if (vertices[next].status == Status::PROCESSING)
            {
                throw std::logic_error("The graph is not acyclic!");
            }
        }
        
        if (stack.top() == current)
        {
            vertices[current].status = Status::PROCESSED;
            vertices[current].time_finish = ++counter;
            stack.pop();
        }
    }
}

/**
 * @brief Performs depth-first-seach on an undirected graph
 *
 * @complexity O(V + E)
 */
void dfs(std::vector<std::vector<int64_t>> &graph, std::vector<Vertex> &vertices)
{
    int64_t component{0};

    for (auto &vertex : vertices)
    {
        if (vertex.status == Status::UNPROCESSED)
        {
            vertex.connectivity_component = ++component;
            dfs_visit(graph, vertices, vertex.id);
        }
    }
}

int main()
{
    int n, a;
    std::cin >> n;
    std::vector<Vertex> vertices;
    std::vector<std::vector<int64_t>> graph(n);

    for (int i{0}; i < n; ++i)
    {
        vertices.push_back(Vertex(i));
    }

    for (int i{0}; i < n; ++i)
    {
        for (int j{0}; j < n; ++j)
        {
            std::cin >> a;
            if (a)
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    dfs(graph, vertices);
}
