#include <iostream>

template <typename T>
class Queue {
public:
    ~Queue() {delete[] array;}

    void enqueue(T value) {
        if (size == capacity) {
            T* temp_array {new T [capacity * 2]};

            for (size_t i{0}; i + head < capacity; ++i) {
                temp_array[i] = array[head + i];
            }

            for (size_t i{0}; i < head; ++i) {
                temp_array[i + capacity - head] = array[i];
            }

            head = 0;
            tail = capacity;

            delete[] array;
            array = temp_array;
            capacity *= 2;
        }

        array[tail] = value;

        tail = (tail + 1) % capacity;
    }

    T dequeue() {
        T x{array[head]};

        head = (head + 1) % capacity;
        return x;
    }

    bool is_empty() {return size == 0;}
private:
    T * array {new T [8]};
    size_t capacity {8};
    size_t size {0};
    size_t head {0};
    size_t tail {0};
};

int main() {
    Queue<int64_t> q;
    q.enqueue(50);
    q.enqueue(100);

    std::cout << q.dequeue() << std::endl << q.dequeue() << std::endl;
    return 0;
}
