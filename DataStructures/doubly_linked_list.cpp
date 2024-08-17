#include <iostream>

template <typename T>
struct node {
    T key;
    node* next {nullptr};
    node* prev {nullptr};

    node(T t_key) 
        : key(t_key) 
    {}
};

template <typename T>
class list {
private:
    node<T>* head {nullptr};
public:
    ~list() {
        node<T>* current = head;

        while (current) {
            delete current->prev;
            if (!current->next)
                delete current;
            else
                current = current->next;
        }
    }

    T* search(T value) {
        node<T>* current {head};

        while (current) {
            if (current->key == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    void insert(T value) {
        if (!head) {
            head = new node<T>(value);
        } else {
            head->prev = new node<T>(value);
            head->prev->next = head;
        }
        head = head->prev;
    }

    void erase(T value) {
        node<T>* current {search(value)};
        if (current) {
            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;
            if (current->next)
                current->next->prev = current->prev;
            delete current;
        }
    }
};

int main() {
    list<int64_t> l;
    return 0;
}