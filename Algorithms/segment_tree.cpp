#include <iostream>
#include <vector>

#define inf 10e8

void build_segment_tree(std::vector<int> & init_vec, std::vector<int> & tree, size_t l, size_t r, size_t vertex_ind)
{
    if (l + 1 == r) {
        tree[vertex_ind] = init_vec[l];
        return;
    }

    build_segment_tree(init_vec, tree, l, (l + r) / 2, 2 * vertex_ind);
    build_segment_tree(init_vec, tree, (l + r) / 2, r, 2 * vertex_ind + 1);

    tree[vertex_ind] = std::max(tree[2 * vertex_ind], tree[2 * vertex_ind + 1]);
        
}

int find_max(std::vector<int> & tree, size_t l, size_t r, size_t a, size_t b, size_t vertex_ind)
{
    if (a < l || b > r || a >= b) {
        return -inf;
    } else if (a == l && b == r) {
        return tree[vertex_ind];
    } 
    return std::max(find_max(tree, l, (l + r) / 2, a, std::min(b, (l + r) / 2), 2 * vertex_ind), 
                    find_max(tree, (l + r) / 2, r, std::max(a, (l + r) / 2), b, 2 * vertex_ind + 1));
}

int main()
{
    std::vector<int> a = {-2, 5, 1, 0, -20};
    std::vector<int> tree (a.size() * 10);

    build_segment_tree(a, tree, 0, a.size(), 1);

    std::cout << find_max(tree, 0, a.size(), 2, 5, 1) << std::endl;

}