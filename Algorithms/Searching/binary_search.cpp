#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
int64_t binary_search(std::vector<T> const &vec, T value) {
    int64_t l = 0, r = vec.size() - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (vec[mid] == value) return mid;

        if (vec[mid] > value)  r = mid - 1;
        else                   l = mid + 1;
    }

    throw std::logic_error("Value is not represented in the list");
}

int main() {
    std::vector<int> vec {1, 2, 3, 4};
    int64_t index;
    try {
        index = binary_search<int> (vec, 1);
        std::cout << "Success, the element has index: " << index << "\n";
    } catch (std::exception & e) {
        std::cout << e.what() <<"\n";
    }
    return 0;
}