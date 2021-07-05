#include <iostream>

template <typename T>
struct leaf {
    leaf * parent { nullptr };
    leaf * left   { nullptr };
    leaf * right  { nullptr };
    T key;

    leaf(T _key) : key { _key } {}
};

template <typename T>
class tree {
private:
    leaf<T> * root { nullptr };
    void clear(leaf<T> * _root) {
        if (_root) {
            clear(_root->left);
            clear(_root->right);
            delete _root;
        }
    }
public:
    ~tree() {
        clear(root);
    }
    void insert(T _key) {
        if (!root) {
            root = new leaf<T> (_key);
        } else {
            leaf<T> * current { root };

            while (current->left || current->right) {
                if (!current->left && current->key >= _key) {
                    current->left = new leaf<T> (_key);
                    current->left->parent = current;
                    break;
                }
                if (!current->right && current->key <= _key) {
                    current->right = new leaf<T> (_key);
                    current->right->parent = current;
                    break;
                }
                if (current->key > _key) 
                    current = current->left;
                else 
                    current = current->right;
            }
            if (!current->left && !current->right) {
                if (current->key > _key) {
                    current->left = new leaf<T> (_key);
                    current->left->parent = current;
                }
                else {
                    current->right = new leaf<T> (_key);
                    current->right->parent = current;
                }
            }
        }
    }
    leaf<T> * get_root() { return root; }

    void inorder(leaf<T> * _root) {
        if (_root) {
            inorder(_root->left);
            std::cout << _root->key << " ";
            inorder(_root->right);
        }
    }
};


int main() {
    tree<int> t;
    for (int i = 0; i < 100; ++i) {
        t.insert(i);
    }
    t.inorder(t.get_root());
}