#include <iostream>

template <typename T>
struct Node
{
    T key;
    Node *next{nullptr};
    Node *prev{nullptr};

    Node(T key_)
        : key(key_)
    {}
};

template <typename T>
class List
{
public:
    ~List()
    {
        Node<T> *current{head};
        while (current)
        {
            Node<T> *next_node{current->next};
            delete current;
            current = next_node;
        }
    }
    
    Node<T> *search(T value)
    {
        Node<T> *current{head};
        
        while (current)
        {
            if (current->key == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void insert(T value)
    {
        if (head == nullptr)
        {
            head = new Node<T>(value);
        }
        else
        {
            head->prev = new Node<T>(value);
            head->prev->next = head;
            head = head->prev;
        }
    }
    
    void erase(T value)
    {
        Node<T> *current{search(value)};
        if (current)
        {
            if (current->prev)
            {
                current->prev->next = current->next;
            }
            else
            {
                head = current->next;
            }
            
            if (current->next)
            {
                current->next->prev = current->prev;
            }
            
            delete current;
        }
    }
private:
    Node<T> *head{nullptr};
};

int main()
{
    List<int64_t> l;
    l.insert(5);
    
    std::cout << l.search(5)->key;
    return 0;
}