#include <iostream>

template <typename T>
class queue {
private:
    T * array     { new T [8] };
    int64_t size  { 8 };
    int64_t head  { 0 };
    int64_t tail  { 0 };
public:

    ~queue() { delete [] array; }

    void enqueue(T value) {

        if (tail == head) {
            T * temp_array { new T [size * 2] };

            for (int64_t i = 0; i < size; ++i) {
                temp_array[i] = array[i];
            }

            delete [] array;
            array = temp_array;
            size *= 2;
        }

        array[tail] = value;

        tail = (tail + 1) % size;
    }

    T dequeue() {
        T x = array[head];

        head = (head + 1) % size;
        return x;
    }

    bool is_empty() { return (head == tail); }
};



int main() {
    queue<int64_t> q;
    q.enqueue(50);
    q.enqueue(100);

    std::cout << q.dequeue() << "\n" << q.dequeue();
    return 0;
}