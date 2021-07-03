#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void insertion_sort(std::vector<T> &vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        for (int64_t j = i; j > 0; --j) {
            if (vec[j] < vec[j-1]) std::swap(vec[j], vec[j-1]);
        }
    }
}


int main() {
    std::vector<int> vec {1, 5, 0, 2, -50};
    insertion_sort<int> (vec);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    return 0;
}