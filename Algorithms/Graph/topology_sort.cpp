#include <iostream>
#include <vector>
#include <list>

#define inf INT64_MAX

enum class status 
{
    unprocessed, processing, processed
};

struct vertex
{
    status  stage       { status::unprocessed };
    int64_t id;

    vertex(int64_t _id) : id(_id) {}
};



void dfs_visit(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices, std::list<size_t>& sorted, int64_t start_id) 
{
    for (auto& x : graph[start_id]) {
        if (vertices[x].stage == status::processing) {
            throw std::logic_error("Graph is not acyclic");
        } else if (vertices[x].stage == status::unprocessed) {
            dfs_visit(graph, vertices, sorted, x);
        }
    }
    vertices[start_id].stage = status::processed;
    
    sorted.push_front(start_id);
}

std::list<size_t> topology_sort(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices) 
{
    std::list<size_t> sorted;

    for (auto& vertex : vertices) {
        if (vertex.stage == status::unprocessed) {
            dfs_visit(graph, vertices, sorted, vertex.id);
        }
    }

    return sorted;
}

int main() 
{
    std::vector<std::vector<int64_t>> graph (7);
    std::vector<vertex> vertices;
    std::list<size_t> sorted;
    int a, b;

    for (int i = 0; i < 6; ++i)
        vertices.push_back(vertex(i));
    for (int i = 0; i < 7; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    sorted = topology_sort(graph, vertices);

    for (auto x : sorted) {
        std::cout << x << ' ';
    }
    
    std::cout << std::endl;
}