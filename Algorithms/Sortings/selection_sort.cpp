#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void selection_sort(std::vector<T> &vec) {
    size_t min_index;
    for (size_t i = 0; i + 1< vec.size(); ++i) {
        min_index = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min_index]) min_index = j;
        }
        std::swap(vec[i], vec[min_index]);
    }
}


int main() {
    std::vector<int> vec {1, 5, 0, 2, -50};
    selection_sort<int> (vec);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    return 0;
}