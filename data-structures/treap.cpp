#include <iostream>
#include <utility>
#include <vector>

struct Node
{
    int64_t key, sum, priority;

    Node *left{nullptr};
    Node *right{nullptr};

    Node(int64_t t_key)
        : key(t_key), priority(std::rand())
    {}
};

/**
 * @brief Tree-like data structure with two fields. In terms of the first
 *        field the treap is a binary search tree, in the terms of the second - heap
 *
 * @complexity Expected tree depth - O(log(n))
 */
class Treap
{
public:
    ~Treap()
    {
        clear(root);
    }

    Node *merge(Node *left, Node *right)
    {
        if (!left)
        {
            return right;
        }
        if (!right)
        {
            return left;
        }

        if (left->priority > right->priority)
        {
            left->right = merge(left->right, right);
            update(left);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }

    std::pair<Node*, Node*> split(Node *tree, int64_t key)
    {
        if (!tree)
        {
            return {nullptr, nullptr};
        }

        if (tree->key <= key)
        {
            auto [left, right] = split(tree->right, key);
            tree->right = left;
            update(tree);
            return {tree, right};
        }
        else
        {
            auto [left, right] = split(tree->left, key);
            tree->left = left;
            update(tree);
            return {left, tree};
        }
    }

    void insert(int64_t key)
    {
        auto [l, r] = split(root, key);
        Node *t = new Node(key);
        root = merge(l, merge(t, r));
    }

    int64_t sum(Node *vertex)
    {
        return vertex ? vertex->sum : 0;
    }

    int64_t sum(int64_t left, int64_t right)
    {
        auto [T, R] = split(root, right);
        auto [L, M] = split(T, left);

        int64_t result = sum(M);
        root = merge(L, merge(M, R));

        return result;
    }

    void update(Node *vertex)
    {
        if (!vertex)
        {
            return;
        }

        vertex->sum = sum(vertex->left) + sum(vertex->right) + vertex->key;
    }
private:
    Node *root{nullptr};

    void clear(Node *node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

int main()
{
    std::vector<int64_t> v = {1, 2, 3, 4};
    Treap t;

    for (int i = 0; i < v.size(); ++i)
    {
        t.insert(v[i]);
    }

    std::cout << t.sum(0, 4) << std::endl;
}