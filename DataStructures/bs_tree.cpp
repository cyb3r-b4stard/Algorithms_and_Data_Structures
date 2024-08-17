#include <iostream>

template <typename T>
struct leaf {
    leaf* parent {nullptr};
    leaf* left   {nullptr};
    leaf* right  {nullptr};
    T key;

    leaf(T t_key) 
        : key {t_key} 
    {}
};

template <typename T>
class tree {
private:
    leaf<T>* root {nullptr};
    
    void clear() {
        if (root) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }
public:
    tree(std::initializer_list<T>& lst) {
        for (T& x : lst)
            this->insert(x);
    }
    
    ~tree() {
        clear();
    }

    void insert(T key) {
        if (!root) {
            root = new leaf<T> (key);
        } else {
            leaf<T>* current        {root};
            leaf<T>* current_parent {nullptr};

            while (current) {  
                current_parent = current;

                if (current->key > key) 
                    current = current->left;
                else 
                    current = current->right;
            }
            if (current_parent->key < key) {
                current_parent->right = new leaf<T> (key);
                current_parent->right->parent = current_parent;
            } else {
                current_parent->left = new leaf<T> (key);
                current_parent->left->parent = current_parent;
            }
        }
    }

    void inorder(leaf<T>* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->key << ' ';
            inorder(node->right);
        }
    }

    leaf<T>* search(T key) {
        leaf<T>* current {root};

        while (current && current->key != key) {
            if (current->key > key)
                current = current->left;
            else 
                current = current->right;
        }

        return current;
    }

    leaf<T>* min(leaf<T>* node) {
        while (node->left)
            node = node->left;
        
        return node;
    }

    leaf<T>* max(leaf<T>* node) {
        while (node->right)
            node = node->right;
        
        return node;
    }

    leaf<T>* successor(leaf<T>* node) {
        if (node->right)
            return min(node->right);
        
        leaf<T>* current_parent {node->parent};
        leaf<T>* current        {node};

        while (current_parent && current == current_parent->right) {
            current = current_parent;
            current_parent = current_parent->parent;
        }
        
        return current_parent;
    }

    leaf<T>* predecessor(leaf<T>* node) 
    {
        if (node->left)
            return max(node->left);
        
        leaf<T>* current_parent {node->parent};
        leaf<T>* current        {node};

        while (current_parent && current == current_parent->left) {
            current = current_parent;
            current_parent = current_parent->parent;
        }

        return current_parent;
    }
};


int main() {
    tree<int> t {15, 6, 18, 3, 2, 4, 7, 13, 9, 17, 20};
    std::cout << t.predecessor(t.search(15))->key;
}
