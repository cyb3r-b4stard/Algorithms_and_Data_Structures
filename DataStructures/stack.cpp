#include <iostream>

template <typename T>
class stack {
private:
    int64_t * array { new int64_t [8] };
    int64_t size    { 8 };
    int64_t top     { 0 };
public:

    ~stack() { delete [] array; }

    void push(T value) {
        if (top == size) {
            int64_t * temp_array { new int64_t [size * 2] };

            for (int64_t i = 0; i < size; ++i) {
                temp_array[i] = array[i];
            }

            delete [] array;
            array = temp_array;
            size *= 2;
        }

        array[top++] = value;
    }

    T pop() { return array[--top];}

    bool is_empty() { return (top == 0); }
};



int main() {
    stack<int64_t> s;
    s.push(50);
    s.push(100);
    std::cout << s.pop() << "\n" << s.pop();
    return 0;
}