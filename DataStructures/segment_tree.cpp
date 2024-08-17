#include <iostream>
#include <vector>

const int64_t inf {INT64_MAX};

void build_segment_tree(std::vector<int64_t>& init_vec, std::vector<int64_t>& tree, size_t l, size_t r, size_t vertex_ind) {
    if (l + 1 == r) {
        tree[vertex_ind] = init_vec[l];
        return;
    }

    build_segment_tree(init_vec, tree, l, (l + r) >> 1, vertex_ind << 1);
    build_segment_tree(init_vec, tree, (l + r) >> 1, r, vertex_ind << 1 + 1);

    tree[vertex_ind] = std::max(tree[vertex_ind << 1], tree[vertex_ind << 1 + 1]);
}

int64_t find_max(std::vector<int64_t>& tree, size_t l, size_t r, size_t a, size_t b, size_t vertex_ind) {
    if (a < l || b > r || a >= b) {
        return -inf;
    } else if (a == l && b == r) {
        return tree[vertex_ind];
    } 
    return std::max(find_max(tree, l, (l + r) >> 1, a, std::min(b, (l + r) >> 1), vertex_ind << 1), 
                    find_max(tree, (l + r) >> 1, r, std::max(a, (l + r) >> 1), b, vertex_ind << 1 + 1));
}

int main()
{
    std::vector<int64_t> a = {-2, 5, 1, 0, -20};
    std::vector<int64_t> tree (a.size() * 2);

    build_segment_tree(a, tree, 0, a.size(), 1);

    std::cout << find_max(tree, 0, a.size(), 2, 4, 1) << std::endl;

}
