#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/**
 * @brief Performs a topology sort on any directed acyclic graph, the resulting 
 *        order obeys the following condition: 
 *        if there is a path a_i -> a_j, then i < j
 * 
 * @complexity O(V + E)
 */

const int64_t inf {INT64_MAX};

enum class status {
    unprocessed, processing, processed
};

struct vertex {
    status  stage {status::unprocessed };
    int64_t id;

    vertex(int64_t _id) 
        : id(_id) 
    {}
};

void dfs_visit(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices, std::vector<int64_t>& sorted, int64_t start_id) {
    std::stack<int64_t> stack;
    int64_t current;
    
    stack.push(start_id);

    while(!stack.empty()) {
        current = stack.top();
        vertices[current].stage = status::processing;

        for (int64_t& next : graph[current]) {
            if (vertices[next].status == status::processing) {
                std::cout << "The graph is not acyclic!" << std::endl;
            } else if (vertoces[next].status == status::unprocessed) {
                stack.push(next);
            }
        }

        if (stack.top() == current) {
            vertices[current].status = status::processed;
            sorted.push_back(current);
            stack.pop();
        }
    }   
}

std::vector<int64_t> topology_sort(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices) {
    std::vector<int64_t> sorted;

    for (auto& vertex : vertices) {
        if (vertex.stage == status::unprocessed) {
            dfs_visit(graph, vertices, sorted, vertex.id);
        }
    }
    std::reverse(sorted.begin(), sorted.end());
    
    return sorted;
}

int main() 
{
    std::vector<std::vector<int64_t>> graph (7);
    std::vector<vertex> vertices;
    std::vector<int64_t> sorted;
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
