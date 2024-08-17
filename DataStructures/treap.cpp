#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Tree-like data structure with two fields. In terms of the first
 *        field the treap is a binary search tree, in the terms of the second - heap
 *        
 * @complexity Expected tree depth - O(log(n))
 */

struct node {
    int64_t key, sum, priority;
    
    node* left {nullptr};
    node* right {nullptr};

    node(int64_t t_key)
        : key(t_key), priority(std::rand())
    {}
};

class treap {
private:
    node* root {nullptr};

    void clear(node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
public:
    treap() = default;

    ~treap() {
        clear(root);
    }

    node* merge(node* left, node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            update(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }

    std::pair<node*, node*> split(node* tree, int64_t key) {
        if (!tree) return {nullptr, nullptr};

        if (tree->key <= key) {
            auto [left, right] = split(tree->right, key);
            tree->right = left;
            update(tree);
            return {tree, right};
        } else {
            auto [left, right] = split(tree->left, key);
            tree->left = left;
            update(tree);
            return {left, tree};
        }
    }

    void insert(int64_t key) {
        auto [l, r] = split(root, key);
        node* t = new node(key);
        root = merge(l, merge(t, r));
    }

    int64_t sum(node* vertex) {
        return vertex ? vertex->sum : 0;
    }

    int64_t sum(int64_t left, int64_t right) {
        auto [T, R] = split(root, right);
        auto [L, M] = split(T, left);

        int64_t result = sum(M);
        root = merge(L, merge(M, R));

        return result;
    }

    void update(node* vertex) {
        if (!vertex) return nullptr;

        vertex->sum = sum(vertex->left) + sum(vertex->right) + vertex->key;
    }
};

int main() {
    std::vector<int64_t> v = {1, 2, 3, 4};
    treap t;

    for (int i = 0; i < v.size(); ++i) {
        t.insert(v[i]);
    }

    std::cout << t.sum(0, 4) << std::endl;
}