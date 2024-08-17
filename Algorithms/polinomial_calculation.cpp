#include <iostream>
#include <vector>

template <typename T>
T polinomial_value(std::vector<T>& vec, T argument) {
    T value {0};
    
    for (int64_t i = vec.size() - 1; i >= 0; --i) {
        value = vec[i] + argument * value;
    }

    return value;
}

int main() {
    std::vector<int> vec {1, 2, 3};
    int value = polinomial_value<int>(vec, 2);
    std::cout << value << "\n";
    return 0;
}