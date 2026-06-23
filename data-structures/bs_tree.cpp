#include <iostream>

template <typename T>
struct Leaf
{
    Leaf *parent{nullptr};
    Leaf *left{nullptr};
    Leaf *right{nullptr};
    T key;

    Leaf(T t_key)
        : key{t_key}
    {}
};

template <typename T>
class Tree
{
public:
    Tree(const std::initializer_list<T> &lst)
    {
        for (auto &x : lst)
            this->insert(x);
    }

    ~Tree()
    {
        clear(root);
    }

    void insert(T key)
    {
        if (!root)
        {
            root = new Leaf<T>(key);
        }
        else
        {
            Leaf<T> *current{root};
            Leaf<T> *current_parent{nullptr};

            while (current)
            {
                current_parent = current;

                if (current->key > key)
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }

            if (current_parent->key < key)
            {
                current_parent->right = new Leaf<T>(key);
                current_parent->right->parent = current_parent;
            }
            else
            {
                current_parent->left = new Leaf<T>(key);
                current_parent->left->parent = current_parent;
            }
        }
    }

    void inorder(Leaf<T> *node)
    {
        if (node)
        {
            inorder(node->left);
            std::cout << node->key << ' ';
            inorder(node->right);
        }
    }

    Leaf<T> *search(T key)
    {
        Leaf<T> *current{root};

        while (current && current->key != key)
        {
            if (current->key > key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return current;
    }

    Leaf<T> *min(Leaf<T> *node)
    {
        while (node->left)
        {
            node = node->left;
        }

        return node;
    }

    Leaf<T> *max(Leaf<T> *node)
    {
        while (node->right)
        {
            node = node->right;
        }

        return node;
    }

    Leaf<T> *successor(Leaf<T> *node)
    {
        if (node->right)
        {
            return min(node->right);
        }

        Leaf<T> *current_parent{node->parent};
        Leaf<T> *current{node};

        while (current_parent && current == current_parent->right)
        {
            current = current_parent;
            current_parent = current_parent->parent;
        }

        return current_parent;
    }

    Leaf<T> *predecessor(Leaf<T> *node)
    {
        if (node->left)
        {
            return max(node->left);
        }

        Leaf<T> *current_parent{node->parent};
        Leaf<T> *current{node};

        while (current_parent && current == current_parent->left)
        {
            current = current_parent;
            current_parent = current_parent->parent;
        }

        return current_parent;
    }
private:
    Leaf<T> *root{nullptr};

    void clear(Leaf<T> *vertex)
    {
        if (vertex)
        {
            clear(vertex->left);
            clear(vertex->right);
            delete vertex;
        }
    }
};

int main()
{
    Tree<int> t{15, 6, 18, 3, 2, 4, 7, 13, 9, 17, 20};
    std::cout << t.predecessor(t.search(15))->key;
}
