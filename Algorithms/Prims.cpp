/* Prim's Algorithm */
#include <iostream>
#include <vector>
#include <cmath>
#define inf 1e9

using namespace std;

int main() {
    vector<vector<pair<int, int>>> edges;
    vector<pair<int, int>>         tree;
    vector<bool>                   visited;
    vector<int>                    vertices,
                                   distance;
    long int n, t, a, b, c, best, minW, current;
    bool flag { true };
    int count { 0 };

    cin >> n >> t;

    for (int i = 0; i < n; ++i) {
        vertices.push_back(i);
        distance.push_back(inf);
        visited.push_back(false);
        edges.push_back(vector<pair<int, int>> {});
    }

    for (int j = 0; j < t; ++j) {
        cin >> a >> b >> c;
        edges[a].push_back(make_pair(b, c));
        edges[b].push_back(make_pair(a, c));
    }

    distance[0] = 0;
    visited[0]  = true;

    for (pair<int, int> vertex: edges[0]) {
        if (!visited[vertex.first]) {
            if (distance[vertex.first] > vertex.second) {
                distance[vertex.first] = vertex.second;
            }
        }
    }
    
    while (flag) {
        best = -1;
        minW = inf;
        for (int vertex : vertices) {
            if (!visited[vertex]) {
                if (distance[vertex] < minW) {
                    minW = distance[vertex];
                    best = vertex;
                }
            }
        }
        for (pair<int, int> vertex : edges[best]) {
            if (visited[vertex.first] && vertex.second == minW) current = vertex.first;
        }
        visited[best] = true;
        tree.push_back(make_pair(current, best));
        for (pair<int, int> vertex : edges[best]) {
            if (!visited[vertex.first]) {
                if (distance[vertex.first] > vertex.second) {
                    distance[vertex.first] = vertex.second;
                }
            }
        }
        count = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) count++;
        }
        if (count > 0) flag = true;
        else flag = false;
    }
    for (size_t i = 0; i < tree.size(); ++i) {
        cout << tree[i].first << " " << tree[i].second << "\n";
    }



    return 0;
}
