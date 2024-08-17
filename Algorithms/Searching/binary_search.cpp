#include <iostream>
#include <vector>

template <typename T>
int64_t lower_bound(std::vector<T> const &vec, T value) {
    int64_t l = 0, r = vec.size(), mid;

    while (l < r) {
        mid = (l + r) / 2;

        if (vec[mid] < value) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

template <typename T>
int64_t upper_bound(std::vector<T> const &vec, T value) {
    int64_t l = 0, r = vec.size(), mid;

    while (l < r) {
        mid = (l + r) / 2;

        if (vec[mid] <= value) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int main() {
    std::vector<int> vec {1, 2, 3, 4};
    std::cout << lower_bound(vec, 4) << std::endl;
    std::cout << upper_bound(vec, 4) << std::endl;
    return 0;
}
