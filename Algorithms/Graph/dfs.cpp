#include <iostream>
#include <queue>
#include <vector>

#define inf 1000000000

enum class status {
    unprocessed, processing, processed
};

struct vertex {
    status  stage { status::unprocessed };
    int64_t time_start  { -1 };
    int64_t time_finish { -1 };
    int64_t parent { -1 };
    int64_t id;
    vertex(int64_t _id) : id(_id) {}
};

int64_t counter;


void dfs_visit(std::vector<std::vector<int64_t>> & graph, std::vector<vertex> & vertices, int64_t start_id) {
    vertices[start_id].time_start = ++counter;
    vertices[start_id].stage = status::processing;
    for (auto & x : graph[start_id]) {
        if (vertices[x].stage == status::unprocessed) {
            vertices[x].parent = start_id;
            dfs_visit(graph, vertices, x);
        }
    }
    vertices[start_id].stage = status::processed;
    vertices[start_id].time_finish = ++counter;
}
void dfs(std::vector<std::vector<int64_t>> & graph, std::vector<vertex> & vertices) {
    counter = 0;
    for (auto & vertex : vertices) {
        if (vertex.stage == status::unprocessed)
            dfs_visit(graph, vertices, vertex.id);
    }
}

int main() {
    std::vector<vertex> vertices;
    std::vector<std::vector<int64_t>> graph (7);
    int a, b;
    for (int i = 0; i < 7; ++i)
        vertices.push_back(vertex(i));
    for (int i = 0; i < 5; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(graph, vertices);
}