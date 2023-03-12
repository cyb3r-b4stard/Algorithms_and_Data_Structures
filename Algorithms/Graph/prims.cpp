#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct edge
{
    size_t  from;
    size_t  to;
    int64_t weight;
};

struct compare
{
    bool operator() (const edge& lhs, const edge& rhs)
    {
        return lhs.weight > rhs.weight;
    }
};

std::vector<edge> prims(std::vector<std::list<std::pair<size_t, int64_t>>>& graph)
{
    std::priority_queue<edge, std::vector<edge>, compare> queue;
    std::vector<edge> min_tree;
    std::vector<bool> chosen (graph.size(), false);
    edge curr;

    chosen[0] = true;

    for (auto& e : graph[0])
    {
        queue.push( {0, e.first, e.second} );
    }

    for (size_t i = 1; i < graph.size(); ++i) 
    {
        curr = queue.top();
        queue.pop();

        for (auto& e : graph[curr.to])
        {
            if (!chosen[e.first]) {
                queue.push( {curr.to, e.first, e.second} );
            }
        }
        
        chosen[curr.to] = true;
        min_tree.push_back(curr);
    }

    return min_tree;
}

int main() 
{


    return 0;
}
