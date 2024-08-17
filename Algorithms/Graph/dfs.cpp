#include <iostream>
#include <queue>
#include <vector>
#include <stack>

/**
 * @brief Performs depth-first-seach on an undirected graph
 * 
 * @complexity O(V + E)
 */

enum class status {
    unprocessed, processing, processed
};

struct vertex {
    status  stage {status::unprocessed};
    int64_t time_start  {-1};
    int64_t time_finish {-1};
    int64_t parent {-1};
    int64_t connectivity_component {-1};
    int64_t id;

    vertex(int64_t _id) 
        : id(_id) 
    {}
};



void dfs_visit(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices, int64_t start_id) {
    int64_t counter {0}, current;
    std::stack<int64_t> stack;

    stack.push(start_id);

    while (!stack.empty(0)) {
        current = stack.top();

        vertices[start_id].time_start = ++counter;
        vertices[current].stage = status::processing;

        for (int64_t& next : graph[current]) {
            if (vertices[next].stage == status::unprocessed) {
                vertices[next].parent = current;
                vertices[next].connectivity_component = vertices[current].connectivity_component;
                stack.push(next);
            } else if (vertices[next].stage == status::processing) {
                std::cout << "There is a cycle: " << current << ' ' << next << std::endl;
            }
        }    

        if (stack.top() == current) {
            vertices[current].stage = status::processed;
            vertices[current].time_finish = ++counter;
        }
    }
}

void dfs(std::vector<std::vector<int64_t>>& graph, std::vector<vertex>& vertices) {
    int64_t component {0};

    for (vertex& vertex : vertices) {
        if (vertex.stage == status::unprocessed) {
            vertex.connectivity_component = ++component;
            dfs_visit(graph, vertices, vertex.id);
        }
    }
}

int main() {
    int n, a;
    std::cin >> n;
    std::vector<vertex> vertices;
    std::vector<std::vector<int64_t>> graph (n);

    for (int i = 0; i < n; ++i) {
        vertices.push_back(vertex(i));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a;
            if (a) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    dfs(graph, vertices);
}
