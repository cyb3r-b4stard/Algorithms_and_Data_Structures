#include <iostream>
#include <queue>
#include <list>
#include <vector>

#define inf 1000000000

enum class status {
    unprocessed, processing, processed
};

struct vertex {
    status  stage { status::unprocessed };
    int64_t distance { inf };
    int64_t parent { -1 };
    int64_t id;
    vertex(int64_t _id) : id(_id) {}
};

void bfs(std::vector<std::list<int64_t>> & graph, std::vector<vertex> & vertices, int64_t start) {
    std::queue<int64_t> q;
    int64_t current;

    vertices[start].stage = status::processing;
    vertices[start].distance = 0;
    q.push(start);

    while (!q.empty()) {
        current = q.front();
        q.pop();
        for (int64_t & x : graph[current]) {
            if (vertices[x].stage == status::unprocessed) {
                vertices[x].stage = status::processing;
                vertices[x].distance = vertices[current].distance + 1;
                vertices[x].parent = current;
                q.push(x);
            }
        }
        vertices[current].stage = status::processed;
    }
}

int main() {
    std::vector<std::list<int64_t>> graph (4);
    std::vector<vertex> vertices;
    for (int64_t i = 0; i < graph.size(); ++i) {
        vertices.push_back(vertex(i));
    }
    int a, b;
    for (int i = 0; i < 4; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    bfs(graph, 0);
}